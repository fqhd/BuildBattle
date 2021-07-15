#include "HUD.hpp"

void HUD::init(){
	m_imageRenderer.init();
	addTextures(); // Important to add textures before adding images
	addImages();
}

void HUD::render(){
	m_imageRenderer.renderImage(0); // Rendering the crossbar
}

void HUD::destroy(){
	m_imageRenderer.destroy();
}

void HUD::addTextures(){
	m_imageRenderer.addTexture("res/textures/gui/crosshair.png");
	m_imageRenderer.addTexture("res/textures/gui/img.png");
}

void HUD::addImages(){
	m_imageRenderer.addImage(glm::vec4(628, 348, 16, 16), 0);
}