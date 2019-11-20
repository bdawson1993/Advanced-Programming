#include "GameController.h"

GameController::GameController()
{
	//the default first course
	GolfCourse* course = new GolfCourse(0);
	course->Start();
	loadedCourses.push_back(course);

	GolfCourse* hole2 = new GolfCourse(vec2(1.3f, 2.1f));
	hole2->AddCorner(vec2(-0.6f, -2.6), vec2(-0.6f, 3.2f));
	hole2->AddCorner(vec2(-0.6, 3.2f), vec2(1.6f, 3.2f));
	hole2->AddCorner(vec2(1.6f, 1.0f), vec2(1.6f, 3.2f));

	hole2->AddCorner(vec2(0.7, 1.0f), vec2(1.6f, 1.0f));
	hole2->AddCorner(vec2(0.7f, 1.0f), vec2(0.7f, -2.6f));
	hole2->AddCorner(vec2(0.7f, -2.6f), vec2(-0.6f, -2.6f));
	
	loadedCourses.push_back(hole2);
	


	Player* player = new Player();
	players.push_back(player);
}

GameController::~GameController()
{

}

void GameController::Start()
{
	players[0]->Start();
	
}

void GameController::Update(int ms)
{
	players[0]->Update(ms);
	loadedCourses[1]->Update(ms);
}

void GameController::Input(char key)
{
	players[0]->Input(key);
}

void GameController::SpecialInput(char key)
{
	players[0]->SpecialInput(key);
}

void GameController::Render()
{
	glPushMatrix();
		players[0]->Draw();
	glPopMatrix();

	glPushMatrix();
		loadedCourses[1]->Draw();
	glPopMatrix();
}

GolfCourse GameController::GetCourse(int index)
{
	return *loadedCourses[index];
}

Player GameController::GetPlayer(int index)
{
	return *players[index];
}
