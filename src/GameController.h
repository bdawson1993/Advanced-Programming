#pragma once
#include "GolfCourse.h"
#include "Hole.h"
#include "Player.h"
#include <vector>

class GameController
{
public:
	GameController();
	~GameController();

	void Start();
	void Update(int ms);
	void Input(char key);
	void SpecialInput(char key);
	void Render();

	GolfCourse GetCourse(int index);
	Player GetPlayer(int index);
	void CollisionChecks();

private:
	int currentCourse = 1;
	vector<Player*> players;
	vector<GolfCourse*> loadedCourses;



};

