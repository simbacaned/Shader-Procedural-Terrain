#include "Scene.h"

Scene::Scene(GLFWwindow* window, std::shared_ptr<InputHandler> H) : 
m_window(window),
m_handler(H)
{
	// Shader
	m_terrainShader = std::make_unique<Shader>("..\\shaders\\plainVert.vs", "..\\shaders\\plainFrag.fs", "..\\shaders\\Norms.gs", "..\\shaders\\tessE.tes", "..\\shaders\\tessC.tcs");
	//m_terrainShader = std::make_unique<Shader>("..\\shaders\\plainVert.vs", "..\\shaders\\plainFrag.fs", "..\\shaders\\Norms.gs");
	m_terrainShader->use();
	// Camera & Input
	m_camera = std::make_shared<FirstPersonCamera>(glm::vec3(260, 50, 300));   // xyz argument to set starting position of camera
	m_camera->attachHandler(window, H);
	// Terrain Grid
	m_terrain = std::make_shared<Terrain>();
	setLightingUniforms(m_terrainShader);
	

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

	m_terrain->render();
}

void Scene::setLightingUniforms(std::unique_ptr<Shader>& tess) {
	tess->use();
	//light properties
	glm::vec3 myDirLightPos(.7f, -.6f, .2f);
	tess->setVec3("dirLight.direction", myDirLightPos);
	tess->setVec3("dirLight.ambient", 0.5f, 0.5f, 0.5f);
	tess->setVec3("dirLight.diffuse", 0.55f, 0.55f, 0.55f);
	tess->setVec3("dirLight.specular", 0.6f, 0.6f, 0.6f);
	//material properties
	tess->setVec3("mat.ambient", 0.3, 0.387, 0.317);
	tess->setVec3("mat.diffuse", 0.396, 0.741, 0.691);
	tess->setVec3("mat.specular", 0.297f, 0.308f, 0.306f);
	tess->setFloat("mat.shininess", 0.9f);

}
