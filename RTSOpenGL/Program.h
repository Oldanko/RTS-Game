#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include <GL\glew.h>
#include <glm\glm.hpp>

enum { PROGRAM_ACTOR, PROGRAM_MAIN, PROGRAM_GUI, PROGRAM_GUI_LINES };

class Program
{
public:
	static GLuint mainProgram;
	static GLuint actorProgram;
	static GLuint guiProgram;
	static GLuint guiLinesProgram;

	static void init();
	static void close();
	static void setUniformMVP(int program, glm::mat4 & matrix);
	static void setUniformHealth(int program, float f);
	static GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
};

