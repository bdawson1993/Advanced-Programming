#pragma once
#include <string>
#include "vecmath.h"
#include <GL/glut.h>


using namespace std;


class IGameObject
{
protected:
	string name;
	vec2 posistion;
	


public:
	virtual void Start() = 0;
	virtual void Update(int ms) = 0;
	virtual void Draw() = 0;
};
