#include "TextRenderer.h"

TextRenderer::TextRenderer()
{
	
}

TextRenderer::~TextRenderer()
{
	
}



void TextRenderer::RenderText(string text, int x, int y)
{
	//set to orgo projection
	glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0, width, 0, height);
		glScalef(1, -1, 1);
		glTranslatef(0, -height, 0);
		glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	//render the text to screen
	glPushMatrix();
		glLoadIdentity();
		glRasterPos2f(x, y);
		glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
		const unsigned char* t = reinterpret_cast<const unsigned char*>("text to render");
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, t);
	glPopMatrix();

	//reset projection mode
	glMatrixMode(GL_PROJECTION);
		glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void TextRenderer::Init()
{
	width = glutGet(GLUT_WINDOW_WIDTH);
	height = glutGet(GLUT_WINDOW_HEIGHT);
}
