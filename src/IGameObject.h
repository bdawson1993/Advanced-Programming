#pragma once
#include <string>
#include "vecmath.h"


using namespace std;


class IGameObject
{
private:
	string name;
	vec3 posistion;
	


public:
	virtual void Update();
	virtual void Draw();
};
