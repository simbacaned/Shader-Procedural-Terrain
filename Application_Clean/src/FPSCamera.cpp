#include "FPSCamera.h"



FirstPersonCamera::FirstPersonCamera(glm::vec3 pos) : Camera(pos), m_speed(15.0f), m_sensitivity(0.025f)
{
	m_zoom = 45.0;
	m_yaw = -90.0f;
	m_pitch = 0.0f;
	m_pitchContrain = 89.0f;
	updateCameraVectors();
}

//getters
glm::mat4 FirstPersonCamera::getViewMatrix()
{
	return glm::lookAt(m_position, m_position + m_front, WORLD_UP);

}

glm::mat4 FirstPersonCamera::getProjectionMatrix()
{
	return glm::perspective(glm::radians(m_zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, m_nearP, m_farP);
}

//updates
void FirstPersonCamera::attachHandler(GLFWwindow* W, std::shared_ptr<InputHandler> H)
{
	m_window = W;
	m_handler = H;
}

// Camera Key movement
// Standard WSAD, could extend for any other movement you want ( eg, up, down, etc..)
void FirstPersonCamera::update(float dt)
{
	float vel = m_speed * dt;
	bool mouseMove = m_handler->mouseHasMoved();
	bool isShifted = false;
	if (m_handler->keyHasBeenPressed()) {
		if (m_handler->isKeyPressed(GLFW_KEY_LEFT_SHIFT))
		{
			isShifted = true;
		}
		if (m_handler->isKeyPressed(GLFW_KEY_W)) 
		{
			m_position += m_front * vel * static_cast<float>(1 + isShifted);
		}
		if (m_handler->isKeyPressed(GLFW_KEY_S)) 
		{
			m_position -= m_front * vel * static_cast<float>(1 + isShifted);
		}
		if (m_handler->isKeyPressed(GLFW_KEY_A))
		{
			m_position -= m_right * vel * static_cast<float>(1 + isShifted);
		}
		if (m_handler->isKeyPressed(GLFW_KEY_D)) 
		{
			m_position += m_right * vel * static_cast<float>(1 + isShifted);
		}
		if (m_handler->isKeyPressed(GLFW_KEY_LEFT_CONTROL))
		{
			m_position -= m_up * vel * static_cast<float>(1 + isShifted);
		}
		if (m_handler->isKeyPressed(GLFW_KEY_SPACE))
		{
			m_position -= m_up * -vel * static_cast<float>(1 + isShifted);
		}
	}

	look(m_handler->getMouseDeltaX(), m_handler->getMouseDeltaY());
	zoom(m_handler->getMouseScrollY());

	m_handler->endFrame();  // reset delta values
}



void FirstPersonCamera::updateCameraVectors()
{
	m_front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_front.y = sin(glm::radians(m_pitch));
	m_front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_front = glm::normalize(m_front);
	//re-calculate the Right and Up vector
	m_right = glm::normalize(glm::cross(m_front, WORLD_UP));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	m_up = glm::normalize(glm::cross(m_right, m_front));

}


void FirstPersonCamera::zoom(float offsetY)
{
	float min = 20.0f;
	float max = 45.0f;
	if (m_zoom >= min && m_zoom <= max)
		m_zoom -= offsetY;
	if (m_zoom <= min) m_zoom = min;
	if (m_zoom >= max) m_zoom = max;
}


// move mouse around and update pitch and yaw
void FirstPersonCamera::look(float x, float y)
{


		x *= m_sensitivity;
		y *= m_sensitivity;

		m_yaw += x;
		m_pitch += y;

		if (m_pitch > m_pitchContrain) m_pitch = m_pitchContrain;
		if (m_pitch < -m_pitchContrain) m_pitch = -m_pitchContrain;

		updateCameraVectors();
	

}


