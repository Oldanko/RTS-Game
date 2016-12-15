#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

#include "Program.h"
#include "Controls.h"
#include "Camera.h"

#include "ResourseManager.h"
#include "Node.h"
#include "Actor.h"
#include "Terrain.h"
#include "GUI.h"
#include "Scene.h"

#include "HitBox.h"

using namespace std;

Camera camera;


GLuint loadBMP_custom(const char * imagepath);
void collision(Actor &a, Actor &b);


int main()
{
	WindowManager::init();
	Controls::init();
	ResourceManager::init();
	Program::init();
	
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

	Terrain t;
	Node terrain(t);

	//=======================END GUI===================

	do {
		
		camera.update();
		
		// = = = = = = = = Render = = = = = = = = = =
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		scene.update();
		scene.draw();

		//Textures
		/*
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glUniform1i(glGetUniformLocation(Program::mainProgram, "texture"), 0);
		*/

		//Finish Drawing
		glBindVertexArray(0);
		
		//Update systems
		Controls::update();
	} while (WindowManager::update());

	WindowManager::close();
	ResourceManager::close();
	Program::close();

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