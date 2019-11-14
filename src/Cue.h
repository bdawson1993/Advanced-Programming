#pragma once
#include "IGameObject.h"

class Cue : public IGameObject
{
private:
	vec2 ballPosition;
	float power = 0.25;
	float angle = 0.0;
	

public:
	Cue();
	~Cue();

	void SetBallPosition(vec2 pos);

	// Inherited via IGameObject
	virtual void Start() override;

	virtual void Update(int ms) override;

	virtual void Draw() override;

};


