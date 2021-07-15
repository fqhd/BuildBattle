#pragma once
#include <SFML/Window.hpp>
#include <unordered_map>
#include <glm/glm.hpp>
#include <vector>


class InputManager {
public:

	void init(sf::Window* _window);
	bool processInput();

	bool isKeyPressed(int _keyID);
	bool isKeyReleased(int _keyID);
	bool isKeyDown(int _keyID);
	bool wasKeyDown(int _keyID);

	bool isButtonPressed(int _buttonID);
	bool isButtonReleased(int _buttonID);
	bool isButtonDown(int _buttonID);
	bool wasButtonDown(int _buttonID);


	void setMouseGrabbed(bool _grabbed);
	void setVerticalSync(bool _sync);
	float getDeltaMouseWheel();
	glm::vec2 getWindowSize();
	glm::vec2 getMousePosition();
	glm::vec2 getScaledMousePosition();
	glm::vec2 getPreviousMousePosition();

private:

	// Private functions
	void keyPressed(unsigned int _keyID);
	void keyReleased(unsigned int _keyID);
	void buttonPressed(unsigned int _buttonID);
	void buttonReleased(unsigned int _buttonID);
	

	std::unordered_map<unsigned int, bool> m_keymap;
	std::unordered_map<unsigned int, bool> m_previousKeymap;
	std::unordered_map<unsigned int, bool> m_buttonmap;
	std::unordered_map<unsigned int, bool> m_previousButtonmap;
	glm::vec2 m_windowSize;
	glm::vec2 m_mousePosition;
	glm::vec2 m_previousMousePosition;
	sf::Window* m_window;
	sf::Event m_event;



};

