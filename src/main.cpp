#include <GL/freeglut.h>
#include <iostream>
#include "Camera.h"
#include "GameController.h"

using namespace std;

Camera cam = Camera();
GameController* controller = new GameController();


int time;


void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glLoadIdentity();
	gluLookAt(cam.Position()(0), cam.Position()(1), cam.Position()(2), cam.LookingAt()(0), cam.LookingAt()(1), cam.LookingAt()(2), 0.0f, 1.0f, 0.0f);
	

	glColor3f(1.0, 1.0, 1.0);

	//draw golf course
	glPushMatrix();
		controller->Render();
	glPopMatrix();

	//swap buffers
	glFlush();
	glutSwapBuffers();

	controller->CollisionChecks();

	


}

void SpecKeyboardFunc(int key, int x, int y)
{
	


	controller->SpecialInput(key);
	
}

void SpecKeyboardUpFunc(int key, int x, int y)
{
	
}

void KeyboardFunc(unsigned char key, int x, int y)
{
	
	cam.Update(key, time);
	controller->Input(key);
}

void KeyboardUpFunc(unsigned char key, int x, int y)
{
	
}

void ChangeSize(int w, int h)
{
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0) h = 1;
	float ratio = 1.0 * w / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45, ratio, 0.2, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(0.0,0.7,2.1, 0.0,0.0,0.0, 0.0f,1.0f,0.0f);
	gluLookAt(cam.Position()(0), cam.Position()(1), cam.Position()(2), cam.LookingAt()(0), cam.LookingAt()(1), cam.LookingAt()(2), 0.0f, 1.0f, 0.0f);
}

void InitLights(void)
{
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	GLfloat light_ambient[] = { 2.0, 2.0, 2.0, 1.0 };
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_DEPTH_TEST);
}

void UpdateScene(int ms)
{
	time = ms;
	controller->Update(ms);
	


	glutTimerFunc(10, UpdateScene, 10);
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	//intro and pick mode
	cout << "GOLF GAME " << endl;
	int isNetworked = 0;

	cout << "Would you like a networked game? 1 - yes, 0 - no" << endl;
	cin >> isNetworked;
	if (isNetworked == 1)
		controller = new GameController(0, true);
	else
	{
		int players;
		cout << "How Many Players? " << endl;
		cin >> players;
		controller = new GameController(players, false);
	}



	glutInit(&argc, ((char**)argv));
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1000, 700);
	
	glutCreateWindow("Golf Game");
	glutFullScreen();
	glutDisplayFunc(RenderScene);
	glutTimerFunc(10, UpdateScene, 10);
	glutReshapeFunc(ChangeSize);
	glutIdleFunc(RenderScene);



	glutIgnoreKeyRepeat(0);
	glutKeyboardFunc(KeyboardFunc);
	glutKeyboardUpFunc(KeyboardUpFunc);
	glutSpecialFunc(SpecKeyboardFunc);
	glutSpecialUpFunc(SpecKeyboardUpFunc);
	glEnable(GL_DEPTH_TEST);
	controller->Start();
	

	glutMainLoop();

	return 1;
}

