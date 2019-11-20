#pragma once
#include <GL/freeglut.h>
#include <string>

using namespace std;
class TextRenderer
{
public:
	TextRenderer();
	~TextRenderer();
	void RenderText(string text, int x, int y);
	void Init();

private:
	int width;
	int height;
};

