#pragma once
#include "IGameObject.h"
#include <vector>
#include <iostream>

using namespace std;
struct Corner
{
	vec2 vertice[2];
};


class GolfCourse : public IGameObject
{
public:

	GolfCourse();
	~GolfCourse();

	// Inherited via IGameObject
	virtual void Start() override;

	virtual void Update() override;

	virtual void Draw() override;

private:
	vector<Corner> corners;
	void AddCorner(vec2 i, vec2 y);
	

};



