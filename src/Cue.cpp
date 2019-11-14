#include "Cue.h"

Cue::Cue() : IGameObject()
{

}

Cue::~Cue() 
{
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
