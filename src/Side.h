#pragma once
#include "vecmath.h"

class Side
{
public:
	vec2 vertice[2];
	vec2 centre;
	vec2 normal;

	void CalculateCentre();
	void CalculateNormal();
};

