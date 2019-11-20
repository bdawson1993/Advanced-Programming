#pragma once
#include "IGameObject.h"
#include <vector>
#include <iostream>
#include "Side.h"

using namespace std;



class GolfCourse : public IGameObject
{
public:

	GolfCourse();
	~GolfCourse();

	vector<Side> Corners();

	// Inherited via IGameObject
	virtual void Start() override;

	virtual void Update(int ms) override;

	virtual void Draw() override;

	virtual void Input(char key) override;

	virtual void HasCollided(string name, vec2 collide) override;

	virtual void RenderText() override;

private:
	vector<Side> corners;
	void AddCorner(vec2 i, vec2 y);
	


	

};



