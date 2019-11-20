#include "Hole.h"

Hole::Hole(vec2 pos) : IGameObject()
{
	posistion = pos;
}

Hole::~Hole()
{
}

void Hole::Start()
{
}

void Hole::Draw()
{
	glTranslatef(posistion(0), (radius / 2.0), posistion(1));
	glutWireSphere(radius, 32, 32);
	//glutSolidCube(0.1);
	glColor3f(0, 0, 1.0);
}

void Hole::Input(char key)
{
}

void Hole::HasCollided(string name, vec2 collide)
{
}

void Hole::RenderText()
{
}

void Hole::SpecialInput(char key)
{
}
