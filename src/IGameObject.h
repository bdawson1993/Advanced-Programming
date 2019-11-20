#pragma once
#include <string>
#include "vecmath.h"
#include <GL/glut.h>
#include "TextRenderer.h"


using namespace std;


class IGameObject
{
protected:
	string name;
	vec2 posistion;
	int time;
	TextRenderer text;
	


public:
	void Init() { text.Init(); }
	virtual void Start() = 0;
	virtual void Update(int ms) { time = ms; };
	virtual void Draw() = 0;
	virtual void Input(char key) = 0;
	virtual void SpecialInput(char key) = 0;
	virtual void HasCollided(string name, vec2 collide) = 0;
	virtual void RenderText() = 0;
	vec2 Position();
};
