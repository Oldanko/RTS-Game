#include "ResourseManager.h"

void loadBox(std::vector<GLfloat> &vertices, std::vector<GLuint> &indices);
void loadPlane(std::vector<GLfloat> &vertices, std::vector<GLuint> &indices);

Mesh *ResourceManager::box = nullptr;
Mesh *ResourceManager::plane = nullptr;

void ResourceManager::init()
{
	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;
	loadBox(vertices, indices);
	box = new Mesh(vertices, indices);

	loadPlane(vertices, indices);
	plane = new Mesh(vertices, indices);

}

void ResourceManager::close()
{
	delete box;
	delete plane;
}

void ResourceManager::loadBox(std::vector<GLfloat> &vertices, std::vector<GLuint> &indices)
{
	vertices =
	{
		0.5, 0.0, -0.5, 1.0f / 4.0f, 2.0f / 3.0f, 1.0, 0.0, 0.0,
		0.5, 0.0, 0.5, 0.0f / 4.0f, 2.0f / 3.0f, 1.0, 0.0, 0.0,
		0.5, 1.0, -0.5, 1.0f / 4.0f, 1.0f / 3.0f, 1.0, 0.0, 0.0,
		0.5, 1.0, 0.5, 0.0f / 4.0f, 1.0f / 3.0f, 1.0, 0.0, 0.0,

		-0.5, 0.0, -0.5, 2.0f / 4.0f, 2.0f / 3.0f, 0.0, 0.0, -1.0,
		0.5, 0.0, -0.5, 1.0f / 4.0f, 2.0f / 3.0f, 0.0, 0.0, -1.0,
		-0.5, 1.0, -0.5, 2.0f / 4.0f, 1.0f / 3.0f, 0.0, 0.0, -1.0,
		0.5, 1.0, -0.5, 1.0f / 4.0f, 1.0f / 3.0f, 0.0, 0.0, -1.0,

		-0.5, 0.0, 0.5, 3.0f / 4.0f, 2.0f / 3.0f, -1.0, 0.0, 0.0,
		-0.5, 0.0, -0.5, 2.0f / 4.0f, 2.0f / 3.0f, -1.0, 0.0, 0.0,
		-0.5, 1.0, 0.5, 3.0f / 4.0f, 1.0f / 3.0f, -1.0, 0.0, 0.0,
		-0.5, 1.0, -0.5, 2.0f / 4.0f, 1.0f / 3.0f, -1.0, 0.0, 0.0,

		0.5, 0.0, 0.5, 4.0f / 4.0f, 2.0f / 3.0f, 0.0, 0.0, 1.0,
		-0.5, 0.0, 0.5, 3.0f / 4.0f, 2.0f / 3.0f, 0.0, 0.0, 1.0,
		0.5, 1.0, 0.5, 4.0f / 4.0f, 1.0f / 3.0f, 0.0, 0.0, 1.0,
		-0.5, 1.0, 0.5, 3.0f / 4.0f, 1.0f / 3.0f, 0.0, 0.0, 1.0,

		-0.5, 1.0, -0.5, 2.0f / 4.0f, 1.0f / 3.0f, -1.0, 0.0, 0.0,
		0.5, 1.0, -0.5, 1.0f / 4.0f, 1.0f / 3.0f, -1.0, 0.0, 0.0,
		-0.5, 1.0, 0.5, 2.0f / 4.0f, 0.0f / 3.0f, -1.0, 0.0, 0.0,
		0.5, 1.0, 0.5, 1.0f / 4.0f, 0.0f / 3.0f, -1.0, 0.0, 0.0
	};

	indices =
	{
		1, 0, 2,
		2, 3, 1,

		5, 4, 6,
		6, 7, 5,

		9, 8, 10,
		10, 11, 9,

		13, 12, 14,
		14, 15, 13,

		17, 16, 18,
		18, 19, 17
	};
}

void loadPlane(std::vector<GLfloat> &vertices, std::vector<GLuint> &indices)
{
	vertices =
	{
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f
	};

	indices =
	{
		1, 0, 2,
		1, 3, 2
	};
}