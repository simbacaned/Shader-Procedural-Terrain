#pragma once
#include "FPSCamera.h"
#include "Terrain.h"
#include "Shader.h"
/*
Everything in scene goes here
I'd suggest using this as a base class and extending for specific scenes
*/

class Scene {

public:
	Scene(GLFWwindow* window, std::shared_ptr<InputHandler> H);
	~Scene();
	void update(float dt) ;
private:
	GLFWwindow* m_window;
	std::shared_ptr<InputHandler> m_handler;
	std::shared_ptr<FirstPersonCamera> m_camera;
	std::shared_ptr<Terrain> m_terrain;
	Shader* m_terrainShader;   
	glm::mat4 m_model, m_view, m_projection;

};
