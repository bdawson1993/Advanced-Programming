#include "Side.h"



void Side::Compute()
{
	CalculateCentre();
	CalculateNormal();

	topLeft(0) = vertice[1](0);
	//topLeft(1) = 0.0;
	topLeft(1) = vertice[1](1);
	
	topRight(0) = vertice[0](0);
	//topRight(1) = 0.0;
	topRight(1) = vertice[0](1);

	bottomRight(0) = vertice[0](0);
	//bottomRight(1) = 0.1;
	bottomRight(1) = vertice[0](1);

	bottomLeft(0) = vertice[1](0);
	//bottomLeft(1) = 0.1;
	bottomRight(1) = vertice[1](1);




}

void Side::CalculateCentre()
{
	centre = vertice[0];
	centre += vertice[1];
	centre /= 2.0;

	//cout << centre(0) << ":" << centre(1) << endl;
}

void Side::CalculateNormal()
{
	//can do this in 2d
	vec2 temp = vertice[1] - vertice[0];
	normal(0) = temp(1);
	normal(1) = -temp(0);
	normal.Normalise();
}
