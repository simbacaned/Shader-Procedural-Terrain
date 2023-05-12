#include "Scene.h"

Scene::Scene(GLFWwindow* window, std::shared_ptr<InputHandler> H) : 
m_window(window),
m_handler(H)
{
	// Shader
	m_terrainShader = std::make_unique<Shader>("..\\shaders\\plainVert.vs", "..\\shaders\\plainFrag.fs", "..\\shaders\\Norms.gs", "..\\shaders\\tessE.tes", "..\\shaders\\tessC.tcs");
	m_billboardShader = std::make_unique<Shader>("..\\shaders\\plainVert.vs", "..\\shaders\\plainFrag.fs", "..\\shaders\\billboard.gs");  // billboarding
	//m_terrainShader = std::make_unique<Shader>("..\\shaders\\plainVert.vs", "..\\shaders\\plainFrag.fs", "..\\shaders\\Norms.gs");
	m_terrainShader->use();
	// Camera & Input
	m_camera = std::make_shared<FirstPersonCamera>(glm::vec3(260, 50, 300));   // xyz argument to set starting position of camera
	m_camera->attachHandler(window, H);
	// Terrain Grid
	m_terrain = std::make_shared<Terrain>();
}

void Scene::update(float dt)
{
	m_camera->update(dt); // check for input

	// MVP matrices and uniforms
	// move this to a UBO
	m_projection = glm::perspective(m_camera->getFOV(), (float)SCR_WIDTH / (float)SCR_HEIGHT, NEAR_PLANE, FAR_PLANE);  // values from properties header
	m_view = m_camera->getViewMatrix();
	m_model = glm::mat4(1.0f);
	m_terrainShader->setMat4("projection", m_projection);
	m_terrainShader->setMat4("view", m_view);
	m_terrainShader->setMat4("model", m_model);
	m_terrainShader->setVec3("viewPos", m_camera->getPosition());
	if (m_handler->keyHasBeenPressed()) {
		if (m_handler->isKeyPressed(GLFW_KEY_G))
		{
			gridView = !gridView;
			m_handler ->processedKey(GLFW_KEY_G);
		}
	}
	if (gridView)
	{
		m_terrain->setLine();
	}
	else
	{
		m_terrain->setFill();
	}
	m_terrain->render();
}
