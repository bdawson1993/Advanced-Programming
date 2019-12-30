#pragma once
#include "IGameObject.h"

class Put : public IGameObject
{
private:
	vec2 ballPosition;
	float power = -0.25;
	float angle = 0.0;
	//float force;
	

public:
	Put();
	~Put();

	vec2 Force();

	void SetBallPosition(vec2 pos);

	// Inherited via IGameObject
	virtual void Start() override;

	virtual void Update(int ms) override;

	virtual void Draw() override;

	virtual void Input(char key) override;

	virtual void HasCollided(string name, vec2 collide) override;

	virtual void RenderText() override;

	virtual void SpecialInput(char key) override;

};


