#include "Player.h"

Player::Player()
{
	ball = new Ball();
	cue = new Cue();
}

Player::~Player()
{
}

void Player::Start()
{
	ball->Init();
}

void Player::Draw()
{
	glPushMatrix();
		ball->Draw();
	glPopMatrix();

	//only draw cue when ball is not moving
	if (ball->Velocity() == vec2(0, 0))
	{
		glPushMatrix();
		cue->Draw();
		glPopMatrix();
	}
	
	
	
}

void Player::Input(char key)
{
	cue->Input(key);

	if ((key == ' ') && (ball->Velocity() == vec2(0,0)))
	{
		ball->ApplyForce(cue->Force());
	}


}

void Player::HasCollided(string name, vec2 collide)
{
	ball->HasCollided(name, collide);
}

void Player::RenderText()
{
}

void Player::Update(int ms)
{
	IGameObject::Update(ms);
	cue->SetBallPosition(ball->Position());
	cue->Update(ms);
	ball->Update(ms);
}

Ball Player::PlayerBall()
{
	return *ball;
}
