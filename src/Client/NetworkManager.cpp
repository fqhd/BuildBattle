#include "NetworkManager.hpp"
#include <iostream>

const unsigned int CLIENT_PORT = 7459;
const unsigned int SERVER_PORT = 7456;
const unsigned int PACKET_TRANSMISSION_FREQUENCY = 10;

void NetworkManager::connectToServer(sf::IpAddress& _ip){
	m_serverIp = _ip;
	m_udpSocket.bind(CLIENT_PORT);
	m_udpSocket.setBlocking(false);

	// Connecting to server
	std::cout << "Connecting..." << std::endl;
	if (m_tcpSocket.connect(m_serverIp, SERVER_PORT) == sf::Socket::Status::Done) {
		Utils::log("NetworkManager: Connected to server with ID: " + std::to_string(m_id));
		sf::Packet packet;
		m_tcpSocket.setBlocking(true);
		if(m_tcpSocket.receive(packet) != sf::Socket::Status::Done){
			Utils::log("Failed to receive packet from server");
			return;
		}
		m_tcpSocket.setBlocking(false);
		packet >> m_id;
	} else {
		Utils::log("NetworkManager: Failed to connect to server");
	}

}

void NetworkManager::receiveGameUpdatePacket(World& _world, ParticleHandler& _pHandler, EntityHandler& _eHandler){
	sf::Packet packet;

	// Receiving packet
	if (m_tcpSocket.receive(packet) == sf::Socket::Done) {

		// Getting packet operation code
		uint8_t code;
		packet >> code;

		// Doing different operations based on the packet code
		if(code == 1){ // A Player has Disconnected
			uint8_t id;
			packet >> id;
			std::cout << "Person: " + std::to_string(id) + " has disconnected" << std::endl;
			_eHandler.removeEntity(id);
		} else if (code == 2){ // Block Update
			int x = 0;
			int y = 0;
			int z = 0;
			uint8_t b = 0;

			packet >> x >> y >> z >> b;

			if (!b) {
				_pHandler.placeParticlesAroundBlock(x, y, z);
			}
			_world.setBlock(x, y, z, b);
		}
	}
}

void NetworkManager::downloadWorld(uint8_t* _data){
	// Receive compressed world packet
	sf::Packet packet;
	m_tcpSocket.setBlocking(true);
	if(m_tcpSocket.receive(packet) != sf::Socket::Status::Done){
		Utils::log("Failed to compressed world data packet from server");
		return;
	}
	m_tcpSocket.setBlocking(false);

	// Calculate and print compression ratio
	double totalWorldSize = WORLD_WIDTH * WORLD_WIDTH * WORLD_HEIGHT * CHUNK_SIZE;
	double packetSize = packet.getDataSize();
	double ratio = (1.0 - packetSize / totalWorldSize) * 100;
	std::cout << "Compression Ratio: " << ratio << "%" << std::endl;

	// Decompress world
	uint8_t blockID = 0;
	uint32_t numBlocks = 0;
	uint32_t index = 0;
	while(packet >> blockID){
		packet >> numBlocks;
		for(unsigned int i = 0; i < numBlocks; i++){
			_data[index] = blockID;
			index++;
		}
	}
}

void NetworkManager::sendPositionDataToServer(Camera& _camera){
	float timeBetweenPackets = 1.0f / PACKET_TRANSMISSION_FREQUENCY;
	if (m_dataFrequencyTimer.getElapsedTime().asSeconds() >= timeBetweenPackets) {
		m_dataFrequencyTimer.restart();

		// We execute this code only a few times per second
		// This code sends the position and camera angles to the server
		// Which will in turn send it to other connected clients except ourselves
		sf::Packet packet;
		glm::vec3 p = _camera.getPosition(); // Camera Position
		packet << m_id << p.x << p.y << p.z << _camera.getPitch() << _camera.getYaw();
		m_udpSocket.send(packet, m_serverIp, SERVER_PORT);
	}
}

void NetworkManager::sendBlockUpdatePacket(const glm::ivec3& _blockPosition, uint8_t _blockType){
	sf::Packet packet;
	packet << (uint8_t)2 << _blockPosition.x << _blockPosition.y << _blockPosition.z << _blockType; // We send the keycode 0 because that is the code for a block update.
	m_tcpSocket.send(packet);
}
