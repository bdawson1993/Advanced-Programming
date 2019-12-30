#include "Player.h"

Player::Player()
{
	ball = new Ball(-2.1);
	put = new Put();
}

Player::~Player()
{
	
}

void Player::Start()
{
	Init();
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
			put->Draw();
		glPopMatrix();
	}
	
	
	
}

void Player::Input(char key)
{
	put->Input(key);

	if ((key == ' ') && (ball->Velocity() == vec2(0,0)))
	{
		ball->ApplyForce(put->Force());
		hitCount++;
	}
}

void Player::HasCollided(string name, vec2 collide)
{
	cout << name << endl;
	ball->HasCollided(name, collide);
}

void Player::RenderText()
{
	text.RenderText("Stroke:" + to_string(hitCount), 10, 10);
}

void Player::Update(int ms)
{
	IGameObject::Update(ms);
	put->SetBallPosition(ball->Position());
	put->Update(ms);
	ball->Update(ms);
}

void Player::SpecialInput(char key)
{
	ball->SpecialInput(key);
	put->SpecialInput(key);
}

Ball Player::PlayerBall()
{
	return *ball;
}

int Player::HitCount()
{
	return hitCount;
}
