#include "Terrain.h"


float linearInterpolaton(float a, float b, float x)
{
	return a*(1 - x) + b*x;
}

Terrain::Terrain()
{

	GLfloat grid[] =
	{
		-10.0f, -10.0f,
		10.0f, -10.0f,
		-10.0f, 10.0f,
		10.0f, 10.0f
	};
	GLfloat heightMap[] = { 1, 1, 1, 1 };

	GLuint indices[] = { 0, 1, 2, 1, 2, 3 };
	
	glGenBuffers(2, m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grid), grid, GL_STATIC_DRAW); 

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(heightMap), heightMap, GL_STATIC_DRAW); 

	glGenBuffers(1, &m_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);



	glGenVertexArrays(1, &m_vao);
	/*glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo[0]);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo[1]);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(GLfloat), (GLvoid*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);

	glBindVertexArray(0);*/
}


Terrain::~Terrain()
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(2, m_vbo);
	glDeleteBuffers(1, &m_ebo);
}

void Terrain::draw()
{
	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}