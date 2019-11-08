#pragma once
#include <string>
#include "vecmath.h"
#include <GL/glut.h>


using namespace std;


class IGameObject
{
private:
	string name;
	vec3 posistion;
	


public:
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
};
