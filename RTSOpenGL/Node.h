#pragma once
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

#include "Mesh.h"
#include "Terrain.h"

class Node
{
protected:
	GLuint m_vao;
	Mesh& mesh;

	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
	bool m_matrixShouldBeCalculated;
	glm::mat4 m_modelMatrix;
public:
	Node(Mesh &m);

	void setPosition(glm::vec3 v);
	void setRotation(glm::vec3 v);
	void setScale(glm::vec3 v);

	glm::vec3 getPosition();
	glm::vec3 getRotation();
	glm::vec3 getScale();

	glm::mat4 getModelMatrix();

	void move(glm::vec3 v);
	void rotate(glm::vec3 v);
	void scale(glm::vec3 v);

	void calculateMatrices();
	void draw();
	~Node();
};

