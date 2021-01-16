#include <SFML/Network.hpp>
#include "Game.hpp"
#include "Constants.hpp"
#include "Window.hpp"
#include "GameStates.hpp"
#include "PauseMenu.hpp"
#include "GUIHandler.hpp"
#include <iostream>


bool getIP(sf::IpAddress& ip);
void runGame(sf::IpAddress &ip);

int main(){

	//Seeding the random function to be completely random each time
	srand(time(0));

	//Getting the ip of the server the client desires to connect to
	sf::IpAddress ip;
	if(!getIP(ip)){
		return 0;
	}

	//Running the game with that requested ip
	runGame(ip);

	return 0;
}

void runGame(sf::IpAddress& ip) {


	//Program Variables
	Player player;
	Game game;
	PauseMenu pause;
	GameStates state;
	Settings settings;
	GUIHandler handler;
	sf::Clock clock;

	//Initializing objects
	Constants::loadFromFile();
	Constants::printDebugMessage();
	settings.readFromFile();
	Window::create(Constants::getScreenWidth(), Constants::getScreenHeight(), "Game", true, true);
	Window::setMouseCursorGrabbed(true);
	InputManager::init(Window::window);
	handler.createWorkspaces(2);
	handler.fonts.emplace_back("res/fonts/ostrich-regular.ttf", 32.0f, 512, 512);
	game.init(ip, handler.workspaces.at(0));
	pause.init(settings, handler.workspaces.at(1));
	handler.init();
	state = GameStates::PLAY;

	clock.restart();
	while(state != GameStates::EXIT){
		Window::clear();

		float deltaTime = clock.restart().asSeconds();
		if(Window::isResized()) game.updateElementsBasedOnResize();

		if(state == GameStates::PLAY){
			game.update(settings, deltaTime, state, player, handler.workspaces.at(0));
			game.render(settings, player, deltaTime);
			handler.renderWorkspace(0);

		}else if(state == GameStates::PAUSE){
			pause.update(state, settings, player, handler.workspaces.at(1));
			game.render(settings, player, deltaTime);
			handler.renderWorkspace(1);
		}

		Window::update();
		if(Window::isCloseRequested()) state = GameStates::EXIT;
	}

	//Save settings to file
	settings.writeToFile();

	//Dellocate memory and free objects
	handler.destroy();
	game.destroy();
	Window::close();

}

bool getIP(sf::IpAddress& ip){

	std::string s;
	std::cout << "Enter server IP: ";
	std::cin >> s;
	ip = s;
	if(s.empty()){
		return false;
	}
	return true;
}
