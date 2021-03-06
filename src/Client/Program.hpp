#pragma once

#include "Player.hpp"
#include "Game.hpp"
#include "PauseMenu.hpp"
#include "Config.hpp"
#include "Settings.hpp"
#include "DebugMenu.hpp"
#include "Engine/GUI/GUIRenderer.hpp"
#include "Engine/GUI/GUIAssets.hpp"
#include <SFML/OpenGL.hpp>


class Program {
public:

	void run(sf::IpAddress& ip);


private:

	void initSystems(sf::IpAddress& ip);
	void gameloop();
	void cleanUp();
	void createWindow();

	GUIAssets m_guiAssets;
	GUIRenderer m_guiRenderer;
	Player m_player;
	Game m_game;
	World m_world;
	NetworkManager m_networkManager;
	PauseMenu m_pause;
	GameStates m_state = GameStates::PAUSE;
	InputManager m_inputManager;
	Config m_config;
	Settings m_settings;
	DebugMenu m_debugMenu;

	sf::Window m_window;
	sf::Clock m_clock;

};
