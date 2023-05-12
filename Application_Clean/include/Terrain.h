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
#include <array>
#include "Shader.h"
#include "PerlinNoise.h"

class Terrain
{
public:
	// constructors
	Terrain(int widthIn, int heightIn, int stepSizeIn);
	Terrain();
	// draw terrain - this function could be moved to a Renderer class and Terrain class submits vertices to renderer
	void render();
	void setLine();
	void setFill();

private:
	std::vector<float> m_vertices;
	unsigned int m_VAO, m_VBO, m_EBO;
	std::array<int, 60> m_indices = {
   0,4,1, 0,9,4, 9,5,4, 4,5,8, 4,8,1,
   8,10,1, 8,3,10, 5,3,8, 5,2,3, 2,7,3,
   7,10,3, 7,6,10, 7,11,6, 11,0,6, 0,1,6,
   6,1,10, 9,0,11, 9,11,2, 9,2,5, 7,2,11
	};
	int m_cellSize = 10;  // size of cell in grid and default values
	int m_width = 50;      // how many cells wide
	int m_height = 50;    // how many cells high (or long)
	PerlinNoise perlin;

	// calculate vertex positions and UV values
	void makeVertices();
	void makeVertex(std::vector<float>& height, int width, int x, int z);
	double cycleOctaves(glm::vec3 pos, int numOctaves);

	// setters
	void setVAO();
	// getters
	int getSize();
	
};
#endif
