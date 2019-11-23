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

	vec2 topLeft;
	vec2 topRight;
	vec2 bottomLeft;
	vec2 bottomRight;

	void Compute();

private:
	void CalculateCentre();
	void CalculateNormal();
};

