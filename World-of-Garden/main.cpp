//#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )

#define GLUT_DISABLE_ATEXIT_HACK

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glew.h>
#include <GL/glut.h>

#include "keyboard.h"
#include "mouse.h"
#include "map.h"

GLint snowman_display_list;

void reshape_init(int w, int h)
{
	if (h == 0)
		h = 1;
	ratio = 1.0f * w / h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(60, ratio, 1, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	flush_view(angle_plane, angle_updown);
}


void drawSnowMan() {


	glColor3f(1.0f, 1.0f, 1.0f);

	// Draw Body	
	glTranslatef(0.0f, 0.75f, 0.0f);
	glutSolidSphere(0.75f, 20, 20);


	// Draw Head
	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidSphere(0.25f, 20, 20);

	// Draw Eyes
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glTranslatef(0.05f, 0.10f, 0.18f);
	glutSolidSphere(0.05f, 10, 10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f, 10, 10);
	glPopMatrix();

	// Draw Nose
	glColor3f(1.0f, 0.5f, 0.5f);
	glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
	glutSolidCone(0.08f, 0.5f, 10, 2);
}



GLuint createDL() {
	GLuint snowManDL;

	// Create the id for the list
	snowManDL = glGenLists(1);

	// start list
	glNewList(snowManDL, GL_COMPILE);

	// call the function that contains the rendering commands
	drawSnowMan();

	// endList
	glEndList();

	return(snowManDL);
}

void initScene() {
	// 第一视角初始位置
	x = 50;
	y = 0;
	z = 50;

	glEnable(GL_DEPTH_TEST);
	snowman_display_list = createDL();

}



void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw ground
	/*glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_QUADS);
	glVertex3f(-100.0f, 0.0f, -100.0f);
	glVertex3f(-100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, -100.0f);
	glEnd();*/

	// Draw 36 SnowMen
	for (int i = -3; i < 3; i++)
	for (int j = -3; j < 3; j++) {
		glPushMatrix();
		glTranslatef(i*10.0, 0, j * 10.0);
		glCallList(snowman_display_list);
		glPopMatrix();
	}

	RenderHeightMap();

	glutSwapBuffers();
}



int main(int argc, char** argv) {
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(350, 150);
	glutInitWindowSize(1024, 768);
	glutCreateWindow("World Of Garden");

	GLenum err = glewInit();
	if (err != GLEW_OK) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		return  -1;
	}
	else {
		fprintf(stdout, "glew loading success\n");
	}

	initKeyBord();
	initMouse();
	initTerran();
	initScene();
	glutReshapeFunc(reshape_init);

	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);




	

	glutMainLoop();
	return 0;
}

