#include "Scene.h"

glm::vec3 Scene::anglesCameraSpace(Actor &actor)
{
	glm::vec4 actorPositionCameraSpace = m_camera.ViewMatrix() * actor.getModelMatrix() * glm::vec4(actor.center, 1);


	float xAng = atan(actorPositionCameraSpace.x / -actorPositionCameraSpace.z);
	float yAng = atan(actorPositionCameraSpace.y / -actorPositionCameraSpace.z);

	float dist = glm::length(
		glm::vec3(
			actorPositionCameraSpace.x,
			actorPositionCameraSpace.y,
			actorPositionCameraSpace.z
			)
		);
	float deltaAng = asin(actor.radius / dist);

	return glm::vec3(xAng, yAng, deltaAng);
}

glm::vec3 Scene::mouse_pick_vector(glm::vec2 mouseCoords)
{
	glm::vec4 ray_eye =
		glm::inverse(WindowManager::projectionMatrix())
		* glm::vec4(
			mouseCoords.x,
			mouseCoords.y,
			-1.0,
			1.0);

	glm::vec4 ray_wor = glm::inverse(m_camera.ViewMatrix()) * glm::vec4(ray_eye.x, ray_eye.y, -1.0, 0.0);

	return glm::normalize(glm::vec3(ray_wor.x, ray_wor.y, ray_wor.z));
}

glm::vec3 Scene::ground_pick(glm::vec3 ray)
{
	glm::vec3 cameraPosition = m_camera.cameraGlobalPosition();

	return glm::vec3
		(
			cameraPosition.x + cameraPosition.y * ray.x / -ray.y,
			0.0f,
			cameraPosition.z + cameraPosition.y * ray.z / -ray.y
			);
}

glm::vec2 screenToClip(glm::vec2 coords)
{
	return glm::vec2(
		(2.0f * coords.x) / WindowManager::width() - 1.0f,
		1.0f - (2.0f * coords.y) / WindowManager::height()
		);
}

float pointToLineDistance(glm::vec3 point, glm::vec3 linePoint, glm::vec3 lineVector)
{
	return glm::length(glm::cross((linePoint - point), lineVector)) / length(lineVector);
}

float distanceSquared(glm::vec3 a, glm::vec3 b)
{
	return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y) + (a.z - b.z)*(a.z - b.z);
}

float distanceSquared(glm::vec2 a, glm::vec2 b)
{
	return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
}

bool within(float a, float b, float x)
{
	return (a > x & b < x) | (a<x & b>x);
}

bool within(float a, float b, float x, float r)
{
	return (a + r > x & b - r < x) | (b + r > x & a - r < x);
}

glm::vec2 anglesCursor(glm::vec2 CoordsClipSpace)
{
	glm::vec4 ruClipCoords = glm::inverse(WindowManager::projectionMatrix()) * glm::vec4(1, 1, 0, 1);
	return glm::vec2(atan(ruClipCoords.x * CoordsClipSpace.x),
		atan(ruClipCoords.y * CoordsClipSpace.y));
}


/*GLuint loadBMP_custom(const char * imagepath) {

	printf("Reading image %s\n", imagepath);

	// Data read from the header of the BMP file
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int imageSize;
	unsigned int width, height;
	// Actual RGB data
	unsigned char * data;

	// Open the file
	FILE * file = fopen(imagepath, "rb");
	if (!file) { printf("%s could not be opened. Are you in the right directory ? Don't forget to read the FAQ !\n", imagepath); getchar(); return 0; }

	// Read the header, i.e. the 54 first bytes

	// If less than 54 bytes are read, problem
	if (fread(header, 1, 54, file) != 54) {
		printf("Not a correct BMP file\n");
		return 0;
	}
	// A BMP files always begins with "BM"
	if (header[0] != 'B' || header[1] != 'M') {
		printf("Not a correct BMP file\n");
		return 0;
	}
	// Make sure this is a 24bpp file
	if (*(int*)&(header[0x1E]) != 0) { printf("Not a correct BMP file\n");    return 0; }
	if (*(int*)&(header[0x1C]) != 24) { printf("Not a correct BMP file\n");    return 0; }

	// Read the information about the image
	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);

	// Some BMP files are misformatted, guess missing information
	if (imageSize == 0)    imageSize = width*height * 3; // 3 : one byte for each Red, Green and Blue component
	if (dataPos == 0)      dataPos = 54; // The BMP header is done that way

										 // Create a buffer
	data = new unsigned char[imageSize];

	// Read the actual data from the file into the buffer
	fread(data, 1, imageSize, file);

	// Everything is in memory now, the file wan be closed
	fclose(file);

	// Create one OpenGL texture
	GLuint textureID;
	glGenTextures(1, &textureID);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

	// OpenGL has now copied the data. Free our own version
	delete[] data;

	// Poor filtering, or ...
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 

	// ... nice trilinear filtering.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Return the ID of the texture we just created
	return textureID;
}
*/


ubyte Squad::ACTIVE[8] = { 0b00000001, 0b00000010, 0b00000100, 0b00001000, 0b00010000, 0b00100000, 0b01000000, 0b10000000 };

Scene::Scene() : m_terrainNode(m_terrain)
{
	fr.setStart(glm::vec2(0, 0));
	fr.setFin(glm::vec2(-0.5, -0.5));
}

void Scene::init(Actor * actors, ubyte numberOfActors)
{
	m_squad.m_actor = actors;
	m_numberOfActors = numberOfActors;
}

void Scene::readControls()
{
	if (Controls::mouseInputs() & RMB_CLICK)
	{
		glm::vec3 ray = mouse_pick_vector(screenToClip(Controls::mouseCoords()));

		Actor * target = nullptr;

		for (int i = 0; i < 3; i++)
		{
			if (m_active & m_squad.ACTIVE[i])
				m_squad.m_actor[i].setDestination(ground_pick(ray));
			m_squad.m_actor[i].hitDetection(m_camera.cameraGlobalPosition(), ray, 0.4);
		}
	}

	if (Controls::mouseInputs() & LMB_PRESS)
	{
		fr.setStart(screenToClip(Controls::mouseCoords()));
		fr.visible = true;
	}
	if (Controls::mouseInputs() & LMB_IS_PRESSED)
	{
		fr.setFin(screenToClip(Controls::mouseCoords()));
	}
	if (Controls::mouseInputs() & LMB_RELEASE)
	{
		fr.visible = false;

		m_active = 0;

		if (Controls::mouseInputs() & LMB_CLICK)
		{
			float distance = 100000000.0f;
			for (int i = 0; i < 3; i++)
			{
				if (pointToLineDistance(
					m_squad.m_actor[i].getPosition() + m_squad.m_actor[i].center,
					m_camera.cameraGlobalPosition(),
					mouse_pick_vector(screenToClip(Controls::mouseCoords())))
					<= m_squad.m_actor[i].radius)
				{
					float dist = distanceSquared(m_camera.cameraGlobalPosition(), m_squad.m_actor[i].getPosition());
					if (distance > dist)
					{
						distance = dist;
						m_active = m_squad.ACTIVE[i];
					}
				}
			}
		}
		else
		{
			glm::vec2 as = anglesCursor(fr.m_start);
			glm::vec2 af = anglesCursor(fr.m_fin);

			for (int i = 0; i < 3; i++)
			{
				glm::vec3 aa = anglesCameraSpace(m_squad.m_actor[i]);

				if (within(as.x, af.x, aa.x, aa.z) & within(as.y, af.y, aa.y) ||
					within(as.x, af.x, aa.x) & within(as.y, af.y, aa.y, aa.z))
				{
					m_active |= m_squad.ACTIVE[i];
					continue;
				}

				for (int j = 0; j < 4; j++)
					if (pointToLineDistance(
						m_squad.m_actor[i].getPosition() + m_squad.m_actor[i].center,
						m_camera.cameraGlobalPosition(),
						mouse_pick_vector(fr.point(j)))
						<= 0.72f)
					{
						m_active |= m_squad.ACTIVE[i];
						break;
					}
			}
		}
	}
}

void Scene::update()
{
	readControls();

	m_camera.update();
	for (int i = 0; i < m_numberOfActors; i++)
	{
		if (m_active & m_squad.ACTIVE[i])
			m_squad.m_actor[i].readControls();
		m_squad.m_actor[i].update();
		m_squad.m_actor[i].calculateMatrices();
	}
}

void Scene::draw()
{
	glEnable(GL_DEPTH_TEST);
	
	glm::mat4 VP = WindowManager::projectionMatrix() * m_camera.ViewMatrix();
	
	glUseProgram(Program::mainProgram);

	Program::setUniformMVP(PROGRAM_MAIN, VP);
	glActiveTexture(GL_TEXTURE0);
	m_terrainNode.draw();

	glUseProgram(Program::actorProgram);

	for (int i = 0; i < m_numberOfActors; i++)
	{
		Program::setUniformMVP(PROGRAM_ACTOR, VP*m_squad.m_actor[i].getModelMatrix());
		Program::setUniformHealth(PROGRAM_ACTOR, m_squad.m_actor[i].health());
		m_squad.m_actor[i].draw();
	}

	glUseProgram(Program::guiLinesProgram);
	if (fr.visible)
		fr.draw();
}


Scene::~Scene()
{
}
