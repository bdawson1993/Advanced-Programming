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

	// Inherited via IGameObject
	virtual void Start() override;

	virtual void Update(int ms) override;

	virtual void Draw() override;

private:
	vector<Side> corners;
	void AddCorner(vec2 i, vec2 y);
	

};



