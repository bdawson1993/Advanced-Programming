#pragma once
#include "vecmath.h"
#include <iostream>

using namespace std;
class Camera
{
	vec3 position;
	vec3 lookingAt;
	float rotSpeed;
	float speed;
	bool rotate = false;

public:
	Camera();
	~Camera();
	void Update(char key, int ms);
	vec3 Position();
	vec3 LookingAt();

private:

};

