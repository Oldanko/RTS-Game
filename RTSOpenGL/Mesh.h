#pragma once

#include <GL/glew.h>
#include <vector>
#include <iostream>

class Mesh
{
protected:
	std::vector<GLfloat> m_vertices;
	std::vector<GLuint> m_elements;
	GLuint m_vbo, m_ebo;
public:
	Mesh() {};
	Mesh(std::vector<GLfloat> vertices, std::vector<GLuint> indices);

	void bindVBO();
	void bindEBO();

	void draw();

	~Mesh();
};

