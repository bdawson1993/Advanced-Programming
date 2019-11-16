#include "Cue.h"

Cue::Cue() : IGameObject()
{

}

Cue::~Cue() 
{
}

vec2 Cue::Force()
{
	vec2 imp( (-sin(angle) * power * 8.0),
		(-cos(angle) * power * 8.0));

		return imp;
}

void Cue::SetBallPosition(vec2 pos)
{
	ballPosition = pos;
}

void Cue::Start()
{
}

void Cue::Update(int ms)
{
	IGameObject::Update(ms);
}

void Cue::Draw()
{

	float x = sin(angle) * power;
	float y = cos(angle) * power;

	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
		glVertex3f(ballPosition(0), (0.05f / 2.0f), ballPosition(1));
		glVertex3f(ballPosition(0) + x, (0.05f / 2.0f), ballPosition(1) + y);
		glColor3f(1.0, 1.0, 1.0);
	glEnd();

}

void Cue::Input(char key)
{
	switch (key)
	{
	case(GLUT_KEY_LEFT):
		angle -= ((2.0f * time) / 1000);
		break;

	case(GLUT_KEY_RIGHT):
		angle += ((2.0f * time) / 1000);
		break;
	}
}

void Cue::HasCollided(string name, vec2 collide)
{
}
