#pragma once
#include "Actor.h"
#include "Camera.h"
#include "Terrain.h"
#include "Program.h"
#include "GUI.h"

struct Squad
{
	static ubyte ACTIVE[8];// = { 0b00000001, 0b00000010, 0b00000100, 0b00001000, 0b00010000, 0b00100000, 0b01000000, 0b10000000 };

	Actor * m_actor;
	ubyte m_active;

	Actor* target() {}
};

class Scene
{
	
	Camera m_camera;
	Terrain m_terrain;
	Node m_terrainNode;
	Squad m_squad;
	ubyte m_numberOfActors;
	ubyte m_active;
	frame fr;

	glm::vec3 mouse_pick_vector(glm::vec2 mouseCoords);
	glm::vec3 ground_pick(glm::vec3 ray);
	glm::vec3 Scene::anglesCameraSpace(Actor &actor);

public:
	Scene();
	void init(Actor *actors, ubyte numberOfActors);
	void readControls();
	void update();
	void draw();


	~Scene();
};

