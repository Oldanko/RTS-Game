#pragma once

#include "Mesh.h"
#include <glm\glm.hpp>


class Terrain
{
	GLuint m_vao, m_ebo;
	GLuint m_vbo[2];
public:
	Terrain();
	~Terrain();
	void draw();
};
