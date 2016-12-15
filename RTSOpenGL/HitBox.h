#pragma once
#include <glm\glm.hpp>

class HitBox
{
	glm::vec3 m_dimentions;
	glm::vec3 m_position;
public:
	HitBox(glm::vec3 dimentions, glm::vec3 position);

	bool intersects(const glm::vec3 &point, glm::vec3 &ray);

	~HitBox();
};