#pragma once
#include "GolfCourse.h"
#include "Hole.h"
#include "Player.h"
#include "Network.h"
#include <vector>
#include "Parser.h"

using namespace std;

class GameController
{
public:
	GameController() {};
	GameController(int localPlayers, bool networked);
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
	int currentCourse = 0;
	int currentPlayer = 0;
	bool networkedGame = 0;

	
	vector<Player*> players;
	vector<GolfCourse*> loadedCourses;
	Network network;
	string dataToSend;
	Parser parser;

	


};

