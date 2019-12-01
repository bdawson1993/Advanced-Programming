#pragma once
#include "IGameObject.h"
#include "Ball.h"
#include "Cue.h"

class Player : public IGameObject
{
public:
	Player();
	~Player();


	// Inherited via IGameObject
	virtual void Start() override;
	virtual void Draw() override;
	virtual void Input(char key) override;
	virtual void HasCollided(string name, vec2 collide) override;
	virtual void RenderText() override;
	virtual void Update(int ms) override;
	virtual void SpecialInput(char key) override;
	Ball PlayerBall();
	int HitCount();

private:
	Ball* ball;
	Cue* cue;
	int hitCount = 0;

	
};
