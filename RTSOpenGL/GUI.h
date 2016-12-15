#pragma once
#include <GL\glew.h>
#include <glm\glm.hpp>

struct frame
{
	GLfloat m_vertices[8];
	GLuint m_indices[8] = { 0, 1, 1, 2, 2, 3, 3, 0 };

	glm::vec2 m_points;

	glm::vec2 m_start;
	glm::vec2 m_fin;

	GLuint m_vao, m_vbo, m_ebo;

	bool visible;

	frame()
	{
		visible = false;
		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);

		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		m_vertices[0] = 0.0f;
		m_vertices[1] = 0.0f;
		m_vertices[2] = 0.5f;
		m_vertices[3] = 0.0f;
		m_vertices[4] = 0.5f;
		m_vertices[5] = 0.5f;
		m_vertices[6] = 0.0f;
		m_vertices[7] = 0.5f;
		glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(GLfloat), m_vertices, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);

		glGenBuffers(1, &m_ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 8 * sizeof(GLuint), m_indices, GL_STATIC_DRAW);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	~frame()
	{
		glDeleteVertexArrays(1, &m_vao);
		glDeleteBuffers(1, &m_vbo);
		glDeleteBuffers(1, &m_ebo);
	}

	void setStart(glm::vec2 start)
	{
		m_start = start;
		m_vertices[0] = m_start.x;
		m_vertices[1] = m_start.y;
		m_vertices[3] = m_start.y;
		m_vertices[6] = m_start.x;
	}

	void setFin(glm::vec2 fin)
	{
		m_fin = fin;
		m_vertices[2] = m_fin.x;
		m_vertices[4] = m_fin.x;
		m_vertices[5] = m_fin.y;
		m_vertices[7] = m_fin.y;

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(GLfloat), m_vertices, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	glm::vec2 point(unsigned char i)
	{
		if(i < 4)
		return glm::vec2(m_vertices[i*2], m_vertices[i*2+1]);
		return glm::vec2();
	}
	
	
	
	void draw()
	{
		glBindVertexArray(m_vao);
		glDrawElements(GL_LINES, 8, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
};

struct rectangle
{
	float guiSquare[16] =
	{
		0.005f, 0.005f, 0.0, 0.0,
		0.35f, 0.005f, 1.0, 0.0,
		0.005f, 0.2f, 0.0, 1.0,
		0.35f, 0.2f, 1.0, 1.0
	};
	
	GLuint guiIndecies[6] =
	{
		0, 1, 2, 3, 2, 1
	};

	float transperency = 0.0f;

	bool drawGUI = false;

	GLuint vao, vbo, ebo;

	rectangle()
	{

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, 16 * sizeof(GLfloat), &guiSquare[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));

		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), &guiIndecies[0], GL_STATIC_DRAW);

		glBindVertexArray(0);
	}

	

};