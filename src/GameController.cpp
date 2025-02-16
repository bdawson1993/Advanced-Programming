#include "GameController.h"

GameController::GameController(int localPlayers, bool networked)
{
	//the default first course
	GolfCourse* course = new GolfCourse(vec2(0, 1.3));
	course->Start();
	loadedCourses.push_back(course);

	//create hole 2
	GolfCourse* hole2 = new GolfCourse(vec2(1.3f, 2.1f));
	hole2->AddCorner(vec2(-0.6f, -2.6f), vec2(-0.6f, 3.2f));
	hole2->AddCorner(vec2(-0.6f, 3.2f), vec2(1.8f, 3.2f));

	hole2->AddCorner(vec2(1.8f, 3.2f), vec2(1.8f, 1.5f));
	hole2->AddCorner(vec2(1.8f, 1.5f), vec2(1.0f, 1.5f));
	
	hole2->AddCorner(vec2(1.0f, 1.5f), vec2(1.0f, -2.6f));
	hole2->AddCorner(vec2(1.0f, -2.6f), vec2(-0.6f, -2.6f));
	loadedCourses.push_back(hole2);
	
	//create hole 3
	GolfCourse* hole3 = new GolfCourse(vec2(1.5f, 4.1f));
	hole3->AddCorner(vec2(-0.6f, -2.6f), vec2(-0.6f, 3.2f));
	hole3->AddCorner(vec2(-0.6f, 3.2f), vec2(0.9f, 3.2f));

	hole3->AddCorner(vec2(0.9f, 3.2f), vec2(0.9f, 4.5f));
	hole3->AddCorner(vec2(0.9f, 4.5f), vec2(1.9f, 4.5f));

	hole3->AddCorner(vec2(1.9f, 4.5f), vec2(1.9f, -2.6f));
	hole3->AddCorner(vec2(1.9f, -2.6f), vec2(-0.6f, -2.6f));
	loadedCourses.push_back(hole3);

	//create hole 4
	GolfCourse* hole4 = new GolfCourse(vec2(-1.0f, -0.9f));
	hole4->AddCorner(vec2(-0.6f, -2.6f), vec2(-0.6f, -1.2f));
	hole4->AddCorner(vec2(-0.6f, -1.2f), vec2(-1.3, -1.2f));

	hole4->AddCorner(vec2(-1.3f, -1.2f), vec2(-1.3f, -0.6f));
	hole4->AddCorner(vec2(-1.3f, -0.6f), vec2(0.5f, -0.6f));

	hole4->AddCorner(vec2(0.5f, -0.6f), vec2(0.5f, -2.6f));
	hole4->AddCorner(vec2(0.5f, -2.6f), vec2(-0.6f, -2.6f));
	
	

	
	loadedCourses.push_back(hole4);

	
	//set all game varibbles 
	networkedGame = networked;

	//keep players less than 5
	if (localPlayers > 5)
	{
		localPlayers = 5;
	}


	//create local players
	if (networked == false)
	{
		for (int i = 0; i < localPlayers; i++)
		{
			Player* player = new Player();
			players.push_back(player);
		}
	}
	else
	{
		//create players and attempt to connect to server
		Player* player = new Player();
		Player* player2 = new Player();
		players.push_back(player);
		players.push_back(player2);
		network.Connect();
		
		cout << "PlayerID: " + to_string(network.PlayerID()) << endl;
	}
	
	
}

GameController::~GameController()
{
	players.clear();
	loadedCourses.clear();
	scoreboard.clear();
}

void GameController::Start()
{
	
	for (int i = 0; i < players.size(); i++)
	{
		players[i]->Start();
	}
}

void GameController::Update(int ms)
{
	textRender.Init();
	//call update
	players[currentPlayer]->Update(ms);
	loadedCourses[currentCourse]->Update(ms);


	//build message for networked game
	if (networkedGame)
	{
		//send data to server - player 1 is the local player
		dataToSend += "BallPos:" + to_string(players[0]->PlayerBall().Position()(0)) + "," + to_string(players[0]->PlayerBall().Position()(1));
		dataToSend += ":CurrentCourse:" + to_string(currentCourse);
		dataToSend += ":" + to_string(network.PlayerID());

		//get response
		string output;
		output = network.SendData(dataToSend);
		dataToSend = "";
		
	
		
		parser.Parse(output);
		if (network.OtherID() >= 0)
		{
			vector<string> msg = parser.Get("BallPos");
			//cout << msg[0] << "," << msg[1] << endl;
			players[network.OtherID()]->PlayerBall().Position(vec2(stof(msg[0]), stof(msg[1])));
			//cout << to_string(players[network.OtherID()]->PlayerBall().Position()(0)) << "," << to_string(players[network.OtherID()]->PlayerBall().Position()(1)) << endl;
		}
		
	}
}

void GameController::Input(char key)
{
	//handle input of local players
	if (networkedGame == true)
		players[network.PlayerID()]->Input(key);
	else //handle local game
		players[currentPlayer]->Input(key);
}

void GameController::SpecialInput(char key)
{

	if (networkedGame == true)
		players[network.PlayerID()]->SpecialInput(key);
	else
		players[currentPlayer]->SpecialInput(key);
}

void GameController::Render()
{
	glPushMatrix();
		players[currentPlayer]->Draw();
	glPopMatrix();

	glPushMatrix();
		loadedCourses[currentCourse]->Draw();
	glPopMatrix();

	
	//only draw base UI when game hasn't ended
	if (!gameHasEnded)
	{
		players[currentPlayer]->RenderText();
		textRender.RenderText("Player " + to_string(currentPlayer + 1) + "s Turn ", (glutGet(GLUT_WINDOW_WIDTH) / 2), 20);
	}
	else
	{
		//game over UI
		textRender.RenderText("Player" + to_string(scoreboard[0].playerNumber + 1) + " Won ", (glutGet(GLUT_WINDOW_WIDTH) / 2), 20);
		for (int i = 0; i < scoreboard.size(); i++)
		{
			textRender.RenderText(to_string(i + 1) +". Player " + to_string(scoreboard[i].playerNumber) + "		Hits" + to_string(scoreboard[i].player.HitCount()),
				(glutGet(GLUT_WINDOW_WIDTH) / 2), 40 + (20 * i));
		}

		
	}
	
	
}

GolfCourse GameController::GetCourse(int index)
{
	return *loadedCourses[index];
}

Player GameController::GetPlayer(int index)
{
	return *players[index];
}

void GameController::CollisionChecks()
{
	//collision checks -- with side
	vector<Side> sides = *loadedCourses[currentCourse]->Corners();

	//pick player based on game type
	Player player;
	if (networkedGame)
		player = *players[network.PlayerID()];
	else
		player = *players[currentPlayer];

	vec2 ballPos = player.PlayerBall().Position();
	for (int i = 0; i != sides.size(); i++)
	{
		if (player.PlayerBall().Velocity().Dot(sides[i].normal) >= 0.0)
		{
			continue; //cannot have hit check next side
		}

		vec2 relPosL = player.PlayerBall().Position() - sides[i].vertice[0];
		float sep = relPosL.Dot(sides[i].normal);

		if (sep > player.PlayerBall().Radius())
		{
			continue;
		}

		
		if (ballPos(0) > sides[i].topLeft(0) && (ballPos(0) > sides[i].topRight(0)))
		{
			continue;
		}

		//not within range of the vertices cannot of hit
		if (ballPos(1) > sides[i].topLeft(1) && (ballPos(1) > sides[i].topRight(1)))
		{
			continue;
		}

		if (networkedGame == true)
			players[network.PlayerID()]->HasCollided("SIDE", sides[i].normal);
		else
			players[currentPlayer]->HasCollided("SIDE", sides[i].normal);
		

	}

	//collision check with hole
	vec2 relPosn = player.PlayerBall().Position() - loadedCourses[currentCourse]->CourseHole().Position();
	float dist = (float)relPosn.Magnitude();
	vec2 relPosNorm = relPosn.Normalise();
	vec2 relVelocity = player.PlayerBall().Velocity() - 0;



	if (relVelocity.Dot(relPosNorm) >= 0.0)
	{
		if (dist < (player.PlayerBall().Radius() + player.PlayerBall().Radius())) //ball and hold has same radius
		{
			if ((networkedGame == false) && (currentPlayer != 0)) //prevent checking of network player
			{
				players[currentPlayer]->HasCollided("HOLE", vec2(0, 0));
			}
			else
			{
				players[0]->HasCollided("HOLE", vec2(0, 0));
			}

			//check if should move to next player or next course
			if (currentPlayer < players.size() - 1)
			{
				currentPlayer++;
			}
			else
			{
				currentPlayer = 0;

				//check if game has ended
				if (currentCourse < loadedCourses.size() - 1)
					currentCourse++;
				else
				{
					gameHasEnded = true;

					//build current players into the scoreboard vector and sort
					for (int i = 0; i < players.size(); i++)
					{
						Score score;
						score.player = *players[i];
						score.playerNumber = i;
						scoreboard.push_back(score);

					}
					Score score;
					sort(scoreboard.begin(), scoreboard.end(), score);
				}
			}
		}
	}


}

bool GameController::SortPlayers(Score play1, Score play2)
{
	return (play1.player.HitCount() < play2.player.HitCount());
}

