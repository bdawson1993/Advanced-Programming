#pragma once
#include "IGameObject.h"
#include <vector>
#include <iostream>
#include "Side.h"
#include "Hole.h"

using namespace std;



class GolfCourse : public IGameObject
{
public:

	GolfCourse(vec2 pos);
	~GolfCourse();

	vector<Side>* Corners();

	// Inherited via IGameObject
	virtual void Start() override;

	virtual void Update(int ms) override;

	virtual void Draw() override;

	virtual void Input(char key) override;

	virtual void HasCollided(string name, vec2 collide) override;

	virtual void RenderText() override;

	virtual void SpecialInput(char key) override;
	void AddCorner(vec2 i, vec2 y);

	Hole CourseHole();

private:
	vector<Side> corners;
	Hole* hole;
	
	


	

};



