#include "GolfCourse.h"

GolfCourse::GolfCourse(vec2 pos)
{
	hole = new Hole(pos);
}

GolfCourse::~GolfCourse()
{
}

vector<Side>* GolfCourse::Corners()
{
	return &corners;
}

void GolfCourse::Start()
{

	AddCorner(vec2(-0.6f, -2.2f), vec2(-0.6f, 2.2f));

	AddCorner(vec2(-0.6f, 2.2f), vec2(0.6f, 2.2f));

	AddCorner(vec2(0.6f, 2.2f), vec2(0.6f, -2.2f));

	AddCorner(vec2(0.6f, -2.2f), vec2(-0.6f, -2.2f));
	
}

void GolfCourse::Update(int ms)
{
}

void GolfCourse::Draw()
{
	glPointSize(15.0);
	//cout << corners.size() << endl;
	for (int i = 0; i != corners.size(); i++)
	{
		glBegin(GL_TRIANGLES);
		glColor3f(1, 1, 1);
			glVertex3f(corners[i].vertice[0](0), 0.0, corners[i].vertice[0](1));
			glVertex3f(corners[i].vertice[0](0), 0.1, corners[i].vertice[0](1));
			glVertex3f(corners[i].vertice[1](0), 0.1, corners[i].vertice[1](1));

			glVertex3f(corners[i].vertice[1](0), 0.0, corners[i].vertice[1](1));
			glVertex3f(corners[i].vertice[1](0), 0.1, corners[i].vertice[1](1));
			glVertex3f(corners[i].vertice[0](0), 0.0, corners[i].vertice[0](1));
		glEnd();

		/*glBegin(GL_POINTS);
		glColor3f(1, 0, 0);
		glVertex3f(corners[i].topLeft(0), 0.0, corners[i].topLeft(2));
		glVertex3f(corners[i].topRight(0), 0.0, corners[i].topRight(2));
		
		
		glEnd();*/
	}

	glPushMatrix();
		hole->Draw();
	glPopMatrix();

}

void GolfCourse::Input(char key)
{
}

void GolfCourse::AddCorner(vec2 i, vec2 y)
{
	Side corner;
	corner.vertice[0] = i;
	corner.vertice[1] = y;
	corner.Compute();

	corners.push_back(corner);

}

Hole GolfCourse::CourseHole()
{
	return *hole;
}

void GolfCourse::HasCollided(string name, vec2 collide)
{
}

void GolfCourse::RenderText()
{
}

void GolfCourse::SpecialInput(char key)
{
}
