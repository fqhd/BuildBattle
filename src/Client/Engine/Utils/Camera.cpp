#include "Camera.hpp"

const float NEAR_DIST = 0.1f;
const float FAR_DIST = 1000.0f;
const float FOV = 90.0f;

void Camera::init(InputManager* _manager) {
	m_position = math::vec3(64.0f, 32.0f, 128.0f);
	m_manager = _manager;
	updateViewMatrix();
	updateProjectionMatrix();
}

void Camera::updateProjectionMatrix() {
	math::uvec2 size = m_manager->getWindowSize();
	m_projectionMatrix = math::perspective(math::toRadians(FOV), size.x / (float)size.y, NEAR_DIST, FAR_DIST);
}

float Camera::getPitch() {
	return m_pitch;
}

float Camera::getYaw() {
	return m_yaw;
}

void Camera::update() {
	calculateCameraVectors(0.3f);
	updateViewMatrix();
}

void Camera::calculateCameraVectors(float sensibility) {
	math::ivec2 previousMousePos = m_manager->getMousePosition();
	m_manager->centerMouse();
	math::ivec2 currentMousePos = m_manager->getMousePosition();

	math::ivec2 deltaMousePos = previousMousePos - currentMousePos;

	m_pitch += deltaMousePos.y * sensibility;
	m_yaw += deltaMousePos.x * sensibility;

	if (m_pitch >= 89.0f) {
		m_pitch = 89.0f;
	}
	if (m_pitch <= -89.0f) {
		m_pitch = -89.0f;
	}

	m_forward.x = cos(math::toRadians(m_yaw)) * cos(math::toRadians(m_pitch));
	m_forward.y = sin(math::toRadians(m_pitch));
	m_forward.z = sin(math::toRadians(m_yaw)) * cos(math::toRadians(m_pitch));
	m_forward = math::normalize(m_forward);
}

const math::mat4& Camera::getViewMatrix() {
	return m_viewMatrix;
}

const math::mat4& Camera::getProjectionMatrix() {
	return m_projectionMatrix;
}

const math::vec3& Camera::getPosition() {
	return m_position;
}

void Camera::setPosition(const math::vec3& vec) {
	m_position = vec;
}

const math::vec3& Camera::getForward() {
	return m_forward;
}

void Camera::setForward(const math::vec3& forward) {
	m_forward = forward;
}

void Camera::updateViewMatrix() {
	m_viewMatrix = math::view(m_position, m_forward);
}
