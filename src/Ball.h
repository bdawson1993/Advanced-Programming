#pragma once
#include "IGameObject.h"
#include <iostream>

using namespace std;

class Ball : public IGameObject
{
private:
	float radius = 0.05f;
	vec2 velocity = vec2(0);

	void ApplyFrictionForce(int ms);

public:
	Ball();
	~Ball();

	vec2 Velocity();
	float Radius();

	void ApplyForce(vec2 force);

	// Inherited via IGameObject
	virtual void Start() override;

	virtual void Update(int ms) override;

	virtual void Draw() override;

	virtual void Input(char key) override;

	virtual void HasCollided(string name, vec2 collide) override;

	virtual void RenderText() override;

};

