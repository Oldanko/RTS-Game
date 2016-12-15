#include "Node.h"

Node::Node(Mesh &m) : mesh(m)
{
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	mesh.bindVBO();
	mesh.bindEBO();
	glBindVertexArray(0);
	m_scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

void Node::setPosition(glm::vec3 v)
{
	m_position = v; 
	m_matrixShouldBeCalculated = true;
}

void Node::setRotation(glm::vec3 v)
{
	m_rotation = v;
	m_matrixShouldBeCalculated = true;
}

void Node::setScale(glm::vec3 v)
{
	m_scale = v;
	m_matrixShouldBeCalculated = true;
}

glm::vec3 Node::getPosition()
{
	return m_position;
}

glm::vec3 Node::getRotation()
{
	return m_rotation;
}

glm::vec3 Node::getScale()
{
	return m_scale;
}

glm::mat4 Node::getModelMatrix()
{
	return m_modelMatrix;
}

void Node::move(glm::vec3 v)
{
	m_position += v;
	m_matrixShouldBeCalculated = true;
}

void Node::rotate(glm::vec3 v)
{
	m_rotation += v;
	m_matrixShouldBeCalculated = true;
}

void Node::scale(glm::vec3 v)
{
	m_scale += v;
	m_matrixShouldBeCalculated = true;
}

void Node::calculateMatrices()
{
	if (m_matrixShouldBeCalculated)
		m_modelMatrix =
			glm::translate(m_position)
			* glm::rotate(m_rotation.x, glm::vec3(1, 0, 0))
			* glm::rotate(m_rotation.z, glm::vec3(0, 0, 1))
			* glm::rotate(m_rotation.y, glm::vec3(0, 1, 0))
			* glm::scale(m_scale);
}

void Node::draw()
{
	glBindVertexArray(m_vao);
	mesh.draw();
}


Node::~Node()
{
	glDeleteVertexArrays(1, &m_vao);
}
