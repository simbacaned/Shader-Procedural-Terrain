#ifndef TERRAIN_H
#define TERRAIN_H

/* Terrain Class

Initially just a grid of cells, height of each vertex is 0.0
X, Z positions are calculated along with their respective UV values
this information is stored in a member VAO
Also included a draw function which renders the initial grid
Use this class as the start point

*/


#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "Shader.h"


class Terrain
{
public:
	// constructors
	Terrain(int widthIn, int heightIn, int stepSizeIn);
	Terrain();
	// draw terrain - this function could be moved to a Renderer class and Terrain class submits vertices to renderer
	void render();


private:
	std::vector<float> m_vertices;
	unsigned int m_VAO, m_VBO;
	int m_cellSize = 10;  // size of cell in grid and default values
	int m_width = 50;      // how many cells wide
	int m_height = 50;    // how many cells high (or long)
	
	// calculate vertex positions and UV values
	void makeVertices();
	void makeVertex(int x, int z);

	// setters
	void setVAO();
	// getters
	int getSize();
	
};
#endif
