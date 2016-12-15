#include "HitBox.h"

#include <iostream>

HitBox::HitBox(glm::vec3 a, glm::vec3 b)
{
	m_dimentions = a;
	m_position = b;
}

bool HitBox::intersects(const glm::vec3 & p, glm::vec3 & r)
{
	glm::vec3 point = p - m_position;

	float k;
	glm::vec2 intersection;
		
	if (point.z * r.z < 0)
	{
		//Front; Z min = const AxAy - AxBy - BxBy - BxAy
		float k = (-m_dimentions.z - point.z) / r.z;

		glm::vec2 intersection = glm::vec2(point.x + r.x * k, point.y + r.y * k);

		if ((intersection.x > -m_dimentions.x &	intersection.x < m_dimentions.x) &
			(intersection.y > -m_dimentions.y &	intersection.y < m_dimentions.y))
			return true;

		//back; Z max = const
		k = (m_dimentions.z - point.z) / r.z;

		intersection = glm::vec2(point.x + r.x * k, point.y + r.y * k);

		if ((intersection.x > -m_dimentions.x &	intersection.x < m_dimentions.x) &
			(intersection.y > -m_dimentions.y &	intersection.y < m_dimentions.y))
			return true;
	}
	
	if (point.y * r.y < 0)
	{
		//Bottom; Y min = const
		k = (-m_dimentions.y - point.y) / r.y;

		intersection = glm::vec2(point.x + r.x * k, point.z + r.z * k);

		if ((intersection.x > -m_dimentions.x &	intersection.x < m_dimentions.x) &
			(intersection.y > -m_dimentions.z &	intersection.y < m_dimentions.z))
			return true;

		//Top; Y max = const
		k = (m_dimentions.y - point.y) / r.y;

		intersection = glm::vec2(point.x + r.x * k, point.z + r.z * k);

		if ((intersection.x > -m_dimentions.x &	intersection.x < m_dimentions.x) &
			(intersection.y > -m_dimentions.z &	intersection.y < m_dimentions.z))
			return true;

	}
	if(point.x * r.x < 0)
	{
		//left; X min = const
		k = (-m_dimentions.x - point.x) / r.x;

		intersection = glm::vec2(point.y + r.y * k, point.z + r.z * k);

		if ((intersection.x > -m_dimentions.y &	intersection.x < m_dimentions.y) &
			(intersection.y > -m_dimentions.z &	intersection.y < m_dimentions.z))
			return true;

		//right; X max = const Can be dismissed
		/*
		k = (m_B.x - point.x) / ray.x;

		intersection = glm::vec2(
			ray.y * k,
			ray.z * k
			);
		*/
	}

	return false;
}

HitBox::~HitBox()
{
}
