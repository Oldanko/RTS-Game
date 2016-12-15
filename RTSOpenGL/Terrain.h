#pragma once

#include "Mesh.h"

class Terrain : public Mesh
{
	static const unsigned int side = 129;
	static const unsigned int size = side*side;
public:
	Terrain();
	~Terrain();
};

