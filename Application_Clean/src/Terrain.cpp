#include "..\include\Terrain.h"
#include "stb_image.h"

// constructors

Terrain::Terrain()
{
	makeVertices();
	setVAO();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);
}

Terrain::Terrain(int widthIn, int heightIn, int stepSizeIn) :
	m_cellSize(stepSizeIn),
	m_width(widthIn),
	m_height(heightIn)
{
	makeVertices();
	setVAO();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);
}

void Terrain::setLine()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Terrain::setFill()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
// render function, binds VAO and makes draw call
// you will certainly want to update this - for example with a renderer class and pass data, material, and model matrix to renderer
void Terrain::render()
{
	glBindVertexArray(m_VAO);
	glDrawArrays(GL_PATCHES, 0, m_vertices.size());
}

// creates VAO and VBO from vertex data
// initially only two layouts - one for position and one for UVs
void Terrain::setVAO()
{
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, (m_vertices.size() * sizeof(GLfloat)), m_vertices.data(), GL_STATIC_DRAW);

	//xyz
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//texture
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

int Terrain::getSize()
{
	return m_vertices.size();
}


void Terrain::makeVertices()
{
	int width = 0, height = 0, channels = 0;
	std::string path = "..\\Textures\\heightMap.jpg";
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

	if (!data)
	{
		std::cout << "Failed to load image at : " << path << std::endl;
	}

	std::vector<float> heights(width * height);
	std::cout << heights.size() << std::endl;
	if (data)
	{
		unsigned char* walker = data;
		for (size_t i = 0; i < heights.size(); i++)
		{
			heights[i] = (float)*walker * (10.f / 255.f) - 5.f;
			walker = walker + channels;
		}
	}
	std::cout << heights.size() << std::endl;

	for (int z = 0; z < m_height; z++) {
		float  offSetZ = z * m_cellSize;
		for (int x = 0; x < m_width; x++) {
			float offSetX = x * m_cellSize;
			makeVertex(heights, width, offSetX, offSetZ);  // a
			makeVertex(heights, width, offSetX, offSetZ + m_cellSize);  // b
			makeVertex(heights, width, offSetX + m_cellSize, offSetZ);   // c
			makeVertex(heights, width, offSetX + m_cellSize, offSetZ);  //d
			makeVertex(heights, width, offSetX, offSetZ + m_cellSize);  //e
			makeVertex(heights, width, offSetX + m_cellSize, offSetZ + m_cellSize);  //f
		}
	}
}

void Terrain::makeVertex(std::vector<float>& height, int width, int x, int z)
{
	glm::vec3 pos = glm::vec3(x, z, 0.001);
	double pn = cycleOctaves(pos, 10);
	//x y z position
	m_vertices.push_back((float)x); //xPos
	m_vertices.push_back(pn); //yPos - always 0 for now. Going to calculate this on GPU - could change to calclaute it here.
	//m_vertices.push_back(0); //yPos - always 0 for now. Going to calculate this on GPU - could change to calclaute it here.
	m_vertices.push_back((float)z); //zPos

	   // add texture coords
	m_vertices.push_back((float)x / (m_width * m_cellSize));
	m_vertices.push_back((float)z / (m_height * m_cellSize));
}
double Terrain::cycleOctaves(glm::vec3 pos, int ocataves)
{
	float total = 0.0f;
	float maxAmplitude = 0.0f;

	float amplitude = 100.0f;
	float frequency = 0.005f;

	for (int i = 0; i < ocataves; i++)
	{
		double x = pos.x * frequency;
		double y = pos.y * frequency;
		total += perlin.noise(x, y, 0.01) * amplitude;
		maxAmplitude += amplitude;
		frequency *= 2;
		amplitude /= 2;
	}
	return ((total / maxAmplitude) - 0.5f) * 300;
}
//void Terrain::makeVertex(std::vector<float>& height, int width, int x, int z)
//{
//	//x y z position
//	m_vertices.push_back((float)x); //xPos
//	m_vertices.push_back(height[x * width + z] * 10); //yPos - always 0 for now. Going to calculate this on GPU - could change to calclaute it here.
//	//m_vertices.push_back(0); //yPos - always 0 for now. Going to calculate this on GPU - could change to calclaute it here.
//	m_vertices.push_back((float)z); //zPos
//
//	   // add texture coords
//	m_vertices.push_back((float)x / (m_width * m_cellSize));
//	m_vertices.push_back((float)z / (m_height * m_cellSize));
//}



