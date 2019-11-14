#include "GolfCourse.h"

GolfCourse::GolfCourse()
{
}

GolfCourse::~GolfCourse()
{
}

void GolfCourse::Start()
{
	AddCorner(vec2(-0.6f, -1.2f), vec2(-0.6f, 1.2f));

	AddCorner(vec2(-0.6f, 1.2f), vec2(0.6f, 1.2f));

	AddCorner(vec2(0.6f, 1.2f), vec2(0.6f, -1.2f));

	//AddCorner(vec2(0.2f, 1.2f), vec2(0.6f, -1.2f));

	AddCorner(vec2(0.6f, -1.2f), vec2(-0.6f, -1.2f));
	
}

void GolfCourse::Update(int ms)
{
}

void GolfCourse::Draw()
{
	for (int i = 0; i != corners.size(); i++)
	{
		glBegin(GL_LINE_LOOP);
			glVertex3f(corners[i].vertice[0](0), 0.0, corners[i].vertice[0](1));
			glVertex3f(corners[i].vertice[0](0), 0.1, corners[i].vertice[0](1));

			glVertex3f(corners[i].vertice[1](0), 0.1, corners[i].vertice[1](1));
			glVertex3f(corners[i].vertice[1](0), 0.0, corners[i].vertice[1](1));
		glEnd();
	}

}

void GolfCourse::Input(char key)
{
}

void GolfCourse::AddCorner(vec2 i, vec2 y)
{
	Side corner;
	corner.vertice[0] = i;
	corner.vertice[1] = y;

	corners.push_back(corner);
}
