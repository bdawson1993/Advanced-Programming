#include "Side.h"

void Side::CalculateCentre()
{
	centre = vertice[0];
	centre += vertice[1];
	centre /= 2.0;

	cout << centre(0) << ":" << centre(1) << endl;
}

void Side::CalculateNormal()
{
	//can do this in 2d
	vec2 temp = vertice[1] - vertice[0];
	normal(0) = temp(1);
	normal(1) = -temp(0);
	normal.Normalise();
}
