#include "Actor.h"

float angle(glm::vec2 a, glm::vec2 b)
{
	return b.x / abs(b.x) * acos(glm::dot(a, b) / (glm::length(a) * glm::length(b)));
}

const glm::vec3 Actor::SCALE_STAND	= glm::vec3(0.5, 1.7, 0.6);
const glm::vec3 Actor::SCALE_CROUCH	= glm::vec3(0.6, 1.0, 0.8);
const glm::vec3 Actor::SCALE_PRONE	= glm::vec3(0.6, 0.4, 1.7);

const glm::vec3 Actor::CENTER_STAND	= glm::vec3(0.0, 0.95f, 0.0);
const glm::vec3 Actor::CENTER_CROUCH = glm::vec3(0.0, 0.5, 0.0);
const glm::vec3 Actor::CENTER_PRONE	= glm::vec3(0.0, 0.2, 0.0);

const float Actor::SPEED_STAND		= 0.1f;
const float Actor::SPEED_CROUCH		= 0.05f;
const float Actor::SPEED_PRONE		= 0.02f;

const HitBox Actor::HITBOX_STAND = HitBox(glm::vec3(0.25, 0.85, 0.3), glm::vec3(0, 0.85, 0));
const HitBox Actor::HITBOX_CROUCH = HitBox(glm::vec3(0.3, 0.5, 0.4), glm::vec3(0, 0.5, 0));
const HitBox Actor::HITBOX_PRONE = HitBox(glm::vec3(0.3, 0.2, 0.85), glm::vec3(0, 0.2, 0));

const glm::vec2 Actor::orientation = glm::vec2(0.0, 1.0);

Actor::Actor() : Node(*ResourceManager::box), m_hitbox(HITBOX_STAND)
{
	m_destination = m_position;
	m_speed = SPEED_STAND;
	center = glm::vec3(0.0, 0.5, 0.0);
	radius = 0.72f;
	m_scale = SCALE_STAND;
	m_health = 1.0;
}

Actor::Actor(Mesh&m) : Node(m), m_hitbox(HITBOX_STAND)
{
	m_destination = m_position;
	m_speed = SPEED_STAND;
	center = glm::vec3(0.0, 0.5, 0.0);
	radius = 0.72f;
	m_scale = SCALE_STAND;
}

Actor::~Actor()
{
}

void Actor::update()
{
	if (m_health < 1.0f)
		m_health += 0.2 * WindowManager::timeDelta();

	if (m_destination != m_position) {
		glm::vec3 dir = m_destination - m_position;
		glm::vec3 trip = glm::normalize(dir) * m_speed;

		if (glm::length(trip) > glm::length(dir))
			m_position = m_destination;
		else
		{
			setRotation(glm::vec3(0, angle(orientation, glm::vec2(dir.x, dir.z)), 0));
			m_position += trip;
		}
	}
}

void Actor::move(glm::vec2 v)
{
	m_position += glm::vec3(v.x, 0.0, v.y);
	m_matrixShouldBeCalculated = true;
}

void Actor::setPosition(glm::vec2 v)
{
	m_position = glm::vec3(v.x, 0.0, v.y);
	m_destination = m_position;
	m_matrixShouldBeCalculated = true;
}

void Actor::setDestination(glm::vec3 destination)
{
	m_destination = destination;
}

glm::vec2 Actor::getPosition2D()
{
	return glm::vec2(m_position.x, m_position.z);
}

void Actor::readControls()
{
	ubyte controls = Controls::actorControls();
	if (controls)
	{
		if (controls & ACTOR_STAND)
			stand();
		if (controls & ACTOR_CROUCH)
			crouch();
		if (controls & ACTOR_PRONE)
			prone();
	}
}

void Actor::stand()
{
	setScale(SCALE_STAND);
	m_speed = SPEED_STAND;
	center = CENTER_STAND;
	m_hitbox = HITBOX_STAND;
}

void Actor::crouch()
{
	setScale(SCALE_CROUCH);
	m_speed = SPEED_CROUCH;
	center = CENTER_CROUCH;
	m_hitbox = HITBOX_CROUCH;
}

void Actor::prone()
{
	setScale(SCALE_PRONE);
	m_speed = SPEED_PRONE;
	center = CENTER_PRONE;
	m_hitbox = HITBOX_PRONE;
}

bool Actor::rayCollision(glm::vec3 point, glm::vec3 ray)
{
	return m_hitbox.intersects(rotateY((point - m_position), -m_rotation.y), rotateY(ray, -m_rotation.y));
}

void Actor::hitDetection(glm::vec3 point, glm::vec3 ray, float dmg)
{
	if (rayCollision(point, ray))
		m_health -= dmg;
}

float Actor::health()
{
	return m_health;
}
