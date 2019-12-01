#pragma once
#include "GolfCourse.h"
#include "Hole.h"
#include "Player.h"
#include "Network.h"
#include <vector>
#include "Parser.h"
#include <algorithm>

using namespace std;

struct Score
{
	bool operator() (Score play1, Score play2) { return (play1.player.HitCount() < play2.player.HitCount()); }

	Player player;
	int playerNumber;
};

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


	bool SortPlayers(Score play1, Score play2);
private:
	int currentCourse = 0;
	int currentPlayer = 0;
	bool networkedGame = 0;
	bool gameHasEnded = false;
	
	vector<Player*> players;
	vector<Score> scoreboard;
	vector<GolfCourse*> loadedCourses;
	Network network;
	string dataToSend;
	Parser parser;
	TextRenderer textRender;
	

	


};



