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

Ball::Ball() : IGameObject()
{
	posistion(1) = -1.9;
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
	if (key == ' ')
	{
		hitCount++;
		
	}

}

void Ball::HasCollided(string name, vec2 collide)
{
	cout << name << endl;
	

	if (name == "SIDE")
	{
		double comp = velocity.Dot(collide) * (1.0 + 0.5f);
		vec2 delta = -(collide * comp);
		velocity += delta;
	}

}

void Ball::RenderText()
{
	string amount = to_string(hitCount);
	text.RenderText("Hit Count: " + amount, 10, 10);
}
