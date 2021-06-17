#include "Player.hpp"
#include "Engine/Utils/Utils.hpp"

const float PLAYER_REACH_DISTANCE = 5.0f;
const float PRECISION = 50.0f;

void Player::update(Camera& camera, ParticleHandler& handler, World& world, NetworkManager& _manager) {

	getVisibleBlocks(camera, world);

	if (!visibleBlocks.lookingAtBlock) return;

	if (InputManager::isButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
		breakBlock(handler, world);
		_manager.sendBlockData(visibleBlocks.breakableBlock, 0);
	} else if (InputManager::isButtonPressed(GLFW_MOUSE_BUTTON_RIGHT)) {
		placeBlock(world);
		_manager.sendBlockData(visibleBlocks.placeableBlock, selectedBlock);
	}

	//We get the visible blocks again to update them after a block has been pressed
	getVisibleBlocks(camera, world);

}

void Player::getVisibleBlocks(Camera& camera, World& world) {
	glm::ivec3 pos = vecToBlock(camera.getPosition());
	visibleBlocks.lookingAtBlock = false;
	visibleBlocks.isInsideBlock = world.getBlock(pos.x, pos.y, pos.z) ? true : false;

	glm::vec3 rayPosition = camera.getPosition();
	for (unsigned int i = 0; i < PRECISION; i++) {
		rayPosition += camera.getForward() * PLAYER_REACH_DISTANCE / PRECISION;

		visibleBlocks.breakableBlock = vecToBlock(rayPosition);
		uint8_t blockID = world.getBlock(visibleBlocks.breakableBlock.x, visibleBlocks.breakableBlock.y, visibleBlocks.breakableBlock.z);

		if (blockID) {
			visibleBlocks.lookingAtBlock = true;
			rayPosition -= camera.getForward() * PLAYER_REACH_DISTANCE / PRECISION;
			visibleBlocks.placeableBlock = vecToBlock(rayPosition);
			break;
		}
	}
}

void Player::placeBlock(World& world) {
	world.setBlock(visibleBlocks.placeableBlock.x, visibleBlocks.placeableBlock.y, visibleBlocks.placeableBlock.z, selectedBlock);
}

void Player::breakBlock(ParticleHandler& handler, World& world) {
	// uint8_t blockID = world.getBlock(visibleBlocks.breakableBlock.x, visibleBlocks.breakableBlock.y, visibleBlocks.breakableBlock.z);
	world.setBlock(visibleBlocks.breakableBlock.x, visibleBlocks.breakableBlock.y, visibleBlocks.breakableBlock.z, 0);
	// handler.placeParticlesAroundBlock(visibleBlocks.breakableBlock.x, visibleBlocks.breakableBlock.y, visibleBlocks.breakableBlock.z);
}

glm::ivec3 Player::vecToBlock(const glm::vec3& vec) {
	return glm::ivec3(floor(vec.x), floor(vec.y), floor(vec.z));
}