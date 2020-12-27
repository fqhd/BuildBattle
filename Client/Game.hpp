#pragma once
#include <SFML/Network.hpp>
#include <GL/glew.h>
#include <glm/gtc/noise.hpp>
#include "InputManager.hpp"
#include "Player.hpp"
#include "ChunkShader.hpp"
#include "Model.hpp"
#include "ModelShader.hpp"
#include "World.hpp"
#include "CubeMap.hpp"
#include "ModelRenderer.hpp"
#include "ParticleRenderer.hpp"
#include "GameStates.hpp"
#include "Settings.hpp"
#include "GUIHandler.hpp"
#include "Assets.hpp"
#include "Window.hpp"


class Game {
public:

     void init(GUIFont* font, sf::IpAddress ip);
     void update(Settings& settings, float deltaTime, GameStates& state, uint8_t blockID);
     void render(Settings& settings, float deltaTime);
     void destroy();

     //Game functions
     void generateColorVector(std::vector<vec3>& colors);
     void generateLocalWorld();
     void generateEntityColors();


private:

     //Game functions
     void calcFps();

     //Engine Variables
     World m_world;
     Player m_player;
     ModelRenderer m_modelRenderer;
     CubeMap m_cubeMap;
     ParticleRenderer m_particleRenderer;
     GUIHandler m_handler;
     Assets m_assets;



     //Game Variables
     std::unordered_map<uint8_t, uint8_t> m_clients;
     std::vector<vec3> m_colors;
     std::vector<ColorRGBA8> m_entityColors;
     std::string m_fpsString;
     unsigned int m_fps;
     sf::Clock m_fpsClock;
     sf::Clock m_clock;
     sf::Clock m_networkBufferClock;
     sf::Clock m_despawnClock;
     sf::TcpSocket m_socket;
     uint8_t* m_data = nullptr;



};
