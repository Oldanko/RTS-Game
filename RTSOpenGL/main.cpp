#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

#include "ShaderManager.h"
#include "Controls.h"
#include "Camera.h"

#include "ResourseManager.h"
#include "Node.h"
#include "Actor.h"
#include "Terrain.h"
#include "GUI.h"
#include "Scene.h"

#include "HitBox.h"

#include <thread>
#include <chrono>

using namespace std;

Camera camera;


void collision(Actor &a, Actor &b);


int main()
{
	WindowManager::init();
	Controls::init();
	ResourceManager::init();
	ShaderManager::init();
	
	Scene scene;

	glClearColor(0.3f, 0.3f, 0.9f, 1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Actor actor[3];
	actor[0].setPosition(glm::vec2(5.0, 5.0));
	actor[1].setPosition(glm::vec2(5.0, 0.5));
	actor[2].setPosition(glm::vec2(0.5, 5.0));

	scene.init(actor, 3);

	byte active = 0;

	std::chrono::high_resolution_clock::time_point time_start;
	std::chrono::high_resolution_clock::time_point time_now = std::chrono::high_resolution_clock::now();

	do {
		time_start = std::chrono::high_resolution_clock::now();
		
		// = = = = = = = = Render = = = = = = = = = =
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		scene.update();
		scene.draw();

		glUseProgram(ShaderManager::terrainProgram);


		//Finish Drawing
		glBindVertexArray(0);
		
		//Update systems
		Controls::update();
		
		time_now = std::chrono::high_resolution_clock::now();
		std::this_thread::sleep_for(std::chrono::milliseconds(15) - (time_now - time_start));

	} while (WindowManager::update());

	WindowManager::close();
	ResourceManager::close();
	ShaderManager::close();

	return 0;
}

//============================Collision============================

void collision(Actor &a, Actor &b)
{
	float distance = glm::distance(a.getPosition2D(), b.getPosition2D());
	if (distance < (a.radius + b.radius))
	{
		glm::vec2 direction = glm::normalize(glm::vec2(b.getPosition2D() - a.getPosition2D()));
		
		std::cout << direction.x << " " << direction.y << "\n";
		a.move(distance / 8 * (-direction));
		b.move(distance / 8 * direction);
	}
}