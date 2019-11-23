#include "GameController.h"

GameController::GameController()
{
	//the default first course
	GolfCourse* course = new GolfCourse(0);
	course->Start();
	loadedCourses.push_back(course);

	GolfCourse* hole2 = new GolfCourse(vec2(1.3f, 2.1f));

	
	hole2->AddCorner(vec2(-0.6f, -2.6f), vec2(-0.6f, 3.2f));
	hole2->AddCorner(vec2(-0.6f, 3.2f), vec2(1.8f, 3.2f));

	hole2->AddCorner(vec2(1.8f, 3.2f), vec2(1.8f, 1.5f));
	hole2->AddCorner(vec2(1.8f, 1.5f), vec2(1.0f, 1.5f));
	
	hole2->AddCorner(vec2(1.0f, 1.5f), vec2(1.0f, -2.6f));
	hole2->AddCorner(vec2(1.0f, -2.6f), vec2(-0.6f, -2.6f));

	
	
	
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

	if (key == '+')
	{
		vector<Side>* sides = loadedCourses[currentCourse]->Corners();
		sides->at(0).vertice[0](0) += 0.1;
	}
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
		loadedCourses[currentCourse]->Draw();
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

void GameController::CollisionChecks()
{
	//collision checks -- with side
	vector<Side> sides = *loadedCourses[currentCourse]->Corners();
	Player player = *players[0];
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

		/*if (ballPos >= sides[i].topLeft || ballPos <= sides[i].topRight)
		{
			continue;
		}*/

		if (ballPos(0) > sides[i].topLeft(0) && (ballPos(0) < sides[i].topRight(0)))
		{
			continue;
		}

		if (ballPos(1) > sides[i].topLeft(1) && (ballPos(1) < sides[i].topRight(1)))
		{
			continue;
		}

	
 		players[0]->HasCollided("SIDE", sides[i].normal);
		

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
			players[0]->HasCollided("HOLE", vec2(0, 0));
			currentCourse++;
		}
	}


}
