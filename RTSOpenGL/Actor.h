#pragma once
#include "Node.h"
#include "ResourseManager.h"
#include "Controls.h"
#include "HitBox.h"

class Actor : public Node
{
	static const glm::vec3 SCALE_STAND;
	static const glm::vec3 SCALE_CROUCH;
	static const glm::vec3 SCALE_PRONE;
	static const glm::vec3 CENTER_STAND;
	static const glm::vec3 CENTER_CROUCH;
	static const glm::vec3 CENTER_PRONE;
	static const float SPEED_STAND;
	static const float SPEED_CROUCH;
	static const float SPEED_PRONE;
	
	static const HitBox HITBOX_STAND;
	static const HitBox HITBOX_CROUCH;
	static const HitBox HITBOX_PRONE;
	
	static const glm::vec2 orientation;

	HitBox m_hitbox;
	glm::vec3 m_destination;
	float m_speed; 
	float m_health;

public:
	Actor();
	Actor(Mesh&m);
	~Actor();
	void update();
	void move(glm::vec2);
	void setPosition(glm::vec2 v);
	void setDestination(glm::vec3 destination);
	glm::vec2 getPosition2D();

	void readControls();

	void stand();
	void crouch();
	void prone();

	bool rayCollision(glm::vec3 point, glm::vec3 ray);
	void hitDetection(glm::vec3 point, glm::vec3 ray, float dmg);
	float health();

	glm::vec3 center;
	float radius;
};

