#pragma once
#include "IGameObject.h"

class Hole : public IGameObject
{

public:
	Hole(vec2 pos);
	Hole();//default
	~Hole();

	// Inherited via IGameObject
	virtual void Start() override;
	virtual void Draw() override;
	virtual void Input(char key) override;
	virtual void HasCollided(string name, vec2 collide) override;
	virtual void RenderText() override;
	virtual void SpecialInput(char key) override;

private:
	float radius = 0.05f;
};
