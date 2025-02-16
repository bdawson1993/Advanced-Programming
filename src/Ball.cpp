#include "Ball.h"

void Ball::ApplyFrictionForce(int ms)
{
	if (velocity.Magnitude() <= 0.0)
	{
		return;
	}

	vec2 acceleration = -velocity.Normalised();
	acceleration *= (0.03f * 9.8f);
	vec2 velocityChange = ((acceleration * ms)) / 1000.0f;

	if (velocityChange.Magnitude() > velocity.Magnitude())
	{
		velocity = 0.0;
	}
	else
	{
		velocity += velocityChange;
	}
}

Ball::Ball(int pos) : IGameObject()
{
	posistion(1) = pos;
	startingPosition = posistion;
	
}

Ball::~Ball()
{
}

vec2 Ball::Velocity()
{
	return velocity;
}

float Ball::Radius()
{
	return radius;
}

void Ball::ApplyForce(vec2 force)
{
	vec2 imp((-sin(0.0) * 0.25 * 8.0),
		(-cos(0.0) * 0.25 * 8.0));
	velocity = force;
}

void Ball::Start()
{
	
}

void Ball::Update(int ms)
{
	//cout << velocity(0) << " " << velocity(1) << endl;
	ApplyFrictionForce(ms);
	posistion += ((velocity * ms) / 1000.0f);

	if (velocity.Magnitude() < 0.01f)
	{
		velocity = 0.0f;
	}

	//top left
	collsionBox[0](0) = posistion(0) + -0.005;
	collsionBox[0](1) = posistion(1) + 0.005;

	//top right
	collsionBox[1](0) = posistion(0) + 0.05;
	collsionBox[1](1) = posistion(1) + 0.005;

	//bottom left
	collsionBox[2](0) = posistion(0) + -0.005;
	collsionBox[2](1) = posistion(0) + -0.005;

	//bottom right
	collsionBox[3](0) = posistion(0) + 0.005;
	collsionBox[3](1) = posistion(0) + -0.005;
}

void Ball::Draw()
{
	glTranslatef(posistion(0), (radius/2.0), posistion(1));
		glutWireSphere(radius, 32, 32);
	//glutSolidCube(0.1);
	glColor3f(0, 0, 1.0);

}

void Ball::Input(char key)
{
	
}

void Ball::HasCollided(string name, vec2 collide)
{
	if (name == "SIDE")
	{
		double comp = velocity.Dot(collide) * (1.0 + 0.5f);
		vec2 delta = -(collide * comp);
		velocity += delta;
	}

	if (name == "HOLE")
	{
		cout << "Potted Ball" << endl;
		posistion = startingPosition;
		velocity = 0.0;
	}

}

void Ball::RenderText()
{
	
}

void Ball::SpecialInput(char key)
{
}
