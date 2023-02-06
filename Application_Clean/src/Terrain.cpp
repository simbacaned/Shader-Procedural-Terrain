#include "..\include\Terrain.h"


// constructors

Terrain::Terrain()
{
	makeVertices();
	setVAO();
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_DEPTH_TEST);
}

Terrain::Terrain(int widthIn, int heightIn, int stepSizeIn) :
   m_cellSize(stepSizeIn),
   m_width(widthIn),
   m_height(heightIn)
{
	makeVertices();
	setVAO();
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_DEPTH_TEST);
}


// render function, binds VAO and makes draw call
// you will certainly want to update this - for example with a renderer class and pass data, material, and model matrix to renderer
void Terrain::render()
{
	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
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
	/* triangle a b c
		   b
		   | \
		   a _ c


		 triangle d f e
		   f _ e
			 \ |
			   d

		 c == d
		 b == f
		 Duplicate vertices, you should add indexing

		a = (x,y,z)
		b = (x, y+1)
		c = (x+1,y)

		d = (x+1,y)
		e = (x, y+1)
		f = (x+1,y+1)

		 each vertex a, b,c, etc. will have 5 data:
		 x y z u v
		  */

	for (int z = 0; z < m_height - 1; z++) {
		float  offSetZ = z * m_cellSize;
		for (int x = 0; x < m_width - 1; x++) {
			float offSetX = x * m_cellSize;
			makeVertex(offSetX, offSetZ);  // a
			makeVertex(offSetX, offSetZ + m_cellSize);  // b
			makeVertex(offSetX + m_cellSize, offSetZ);   // c
			makeVertex(offSetX + m_cellSize, offSetZ);  //d
			makeVertex(offSetX, offSetZ + m_cellSize);  //e
			makeVertex(offSetX + m_cellSize, offSetZ + m_cellSize);  //f
		}
	}
}

void Terrain::makeVertex(int x, int z)
{
		//x y z position
	m_vertices.push_back((float)x); //xPos
	m_vertices.push_back(0.0f); //yPos - always 0 for now. Going to calculate this on GPU - could change to calclaute it here.
	m_vertices.push_back((float)z); //zPos

	   // add texture coords
	m_vertices.push_back((float)x / (m_width * m_cellSize));
	m_vertices.push_back((float)z / (m_height * m_cellSize));
}



