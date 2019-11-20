#pragma once
#include "vecmath.h"
#include <iostream>

using namespace std;

class Side
{
public:
	vec2 vertice[2];
	vec2 centre;
	vec2 normal;

	void CalculateCentre();
	void CalculateNormal();
};

