#pragma once
#include "vecmath.h"

class Camera
{
	vec3 position;
	vec3 lookingAt;
	float rotSpeed;
	float speed;

public:
	Camera();
	~Camera();
	void Update(char key, int ms);
	vec3 Position();
	vec3 LookingAt();

private:

};

