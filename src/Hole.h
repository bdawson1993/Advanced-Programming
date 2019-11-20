#pragma once
#include "IGameObject.h"

class Hole : public IGameObject
{
#define PI 3.14


public:
	Hole(vec2 pos);
	~Hole();

	// Inherited via IGameObject
	virtual void Start() override;
	virtual void Draw() override;
	virtual void Input(char key) override;
	virtual void HasCollided(string name, vec2 collide) override;
	virtual void RenderText() override;

private:
	float radius = 0.05f;
};
