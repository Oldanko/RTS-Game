#include "Terrain.h"



Terrain::Terrain()
{
	m_vertices = std::vector<GLfloat>(size * 8);
	m_elements = std::vector<GLuint>((side - 1)*(side - 1) * 6);

	for (int i = 0; i < side; i++)
		for (int j = 0; j < side; j++)
		{
			int id = (i*side + j) * 8;
			m_vertices[id] = i;
			m_vertices[id + 1] = 0;
			m_vertices[id + 2] = j;
			m_vertices[id + 3] = i;
			m_vertices[id + 4] = j;
			m_vertices[id + 5] = 0;
			m_vertices[id + 6] = 1;
			m_vertices[id + 7] = 0;
		}

	for (int i = 0; i < side-1; i++)
		for (int j = 0; j < side-1; j++)
		{
			int id = (i*(side-1) + j); //i*side + j
			m_elements[id * 6] = i*side + j;
			m_elements[id * 6 + 1] = i*side + j + 1;
			m_elements[id * 6 + 2] = i*side + j + side;
			m_elements[id * 6 + 3] = i*side + j + side;
			m_elements[id * 6 + 4] = i*side + j + 1;
			m_elements[id * 6 + 5] = i*side + j + side + 1;
		}

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(GLfloat), &m_vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &m_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_elements.size() * sizeof(GLuint), &m_elements[0], GL_STATIC_DRAW);
}


Terrain::~Terrain()
{
}
