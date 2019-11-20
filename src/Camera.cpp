#include "Camera.h"

Camera::Camera()
{
	//init base values
	position = vec3(0.0, 0.7, -3.1);
	lookingAt = vec3(0.0, 0.0, 0.0);
	speed = 2.0f;
}

Camera::~Camera()
{
}

void Camera::Update(char key, int ms)
{
	//switch to rotate
	if (key == 'z')
	{
		rotate = !rotate;
	}


	//cout << position(0) << " " << position(1) << " " << position(2) << endl;
	const vec3 up(0.0, 1.0, 0.0);

	//move came left
	if (rotate == false)
	{
		if (key == 'a')
		{
			vec3 camDir = (lookingAt - position).Normalised();
			vec3 localL = up.Cross(camDir);
			vec3 inc = (localL * ((speed * ms) / 1000.0));
			//cout << inc(0) << " " << inc(1) << " " << inc(2) << endl;
			position += inc;
			lookingAt += inc;
		}

		//move cam right
		if (key == 'd')
		{
			vec3 camDir = (lookingAt - position).Normalised();
			vec3 localR = camDir.Cross(up);
			vec3 inc = (localR * ((speed * ms) / 1000.0));
			position += inc;
			lookingAt += inc;
		}

		//move cam up
		if (key == 'w')
		{
			vec3 camDir = (lookingAt - position).Normalised();
			vec3 localR = camDir.Cross(up);
			vec3 localUp = localR.Cross(camDir);
			vec3 inc = (localUp * ((speed * ms) / 1000.0));
			position += inc;
			lookingAt += inc;
		}

		//move cam down
		if (key == 's')
		{
			vec3 camDir = (lookingAt - position).Normalised();
			vec3 localR = camDir.Cross(up);
			vec3 localDown = camDir.Cross(localR);
			vec3 inc = (localDown * ((speed * ms) / 1000.0));
			position += inc;
			lookingAt += inc;
		}
	}
	else
	{
		if (key == 'a')
		{
			vec3 camDir = (lookingAt - position).Normalised();
			vec3 localL = up.Cross(camDir);
			vec3 inc = (localL * ((speed * ms) / 1000.0));
			lookingAt = position + camDir + inc;
		}
		if (key == 'd')
		{
			vec3 camDir = (lookingAt - position).Normalised();
			vec3 localR = up.Cross(camDir);
			vec3 inc = (localR * ((speed * ms) / 1000.0));
			lookingAt = position + camDir - inc;
		}
		if (key == 'w')
		{
			vec3 camDir = (lookingAt - position).Normalised();
			vec3 localR = camDir.Cross(up);
			vec3 localUp = localR.Cross(camDir);
			vec3 inc = (localUp * ((speed * ms) / 1000.0));
			lookingAt = position + camDir + inc;
		}
		if (key == 's')
		{
			vec3 camDir = (lookingAt - position).Normalised();
			vec3 localR = camDir.Cross(up);
			vec3 localUp = localR.Cross(camDir);
			vec3 inc = (localUp * ((speed * ms) / 1000.0));
			lookingAt = position + camDir - inc;
		}
	}

	if (key == 'q')
	{
		vec3 camDir = (lookingAt - position).Normalised();
		vec3 inc = (camDir * ((speed * ms) / 1000.0));
		position += inc;
		lookingAt += inc;
	}

	if (key == 'e')
	{
		vec3 camDir = (lookingAt - position).Normalised();
		vec3 inc = (camDir * ((speed * ms) / 1000.0));
		position -= inc;
		lookingAt -= inc;
	}



}

vec3 Camera::Position()
{
	return position;
}

vec3 Camera::LookingAt()
{
	return lookingAt;
}
