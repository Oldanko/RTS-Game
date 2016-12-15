#pragma once
#include "Mesh.h"

class ResourceManager
{
public:
	static Mesh *box;
	static Mesh *plane;
	static void init();
	static void close();

	static void loadBox(std::vector<GLfloat> &vertices, std::vector<GLuint> &indices);
};
