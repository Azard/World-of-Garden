//#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )

#define GLUT_DISABLE_ATEXIT_HACK

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/glui.h>

#include "keyboard.h"
#include "mouse.h"
#include "map.h"
#include "plants.h"
#include "ui.h"

#define WINDOW_POS_X	300
#define WINDOW_POS_Y	150
#define WINDOW_LENGTH	1024
#define WINDOW_WIDTH	768

GLint snowman_display_list;
int main_window;
UI_set* UI = new UI_set;

void reshape_init(int w, int h)
{
	if (h == 0)
		h = 1;
	ratio = 1.0f * w / h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45, ratio, 1, 1000);

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

GLuint createSnowman() {
	GLuint snowManDL;
	snowManDL = glGenLists(1);
	glNewList(snowManDL, GL_COMPILE);
	drawSnowMan();
	glEndList();
	return(snowManDL);
}

void initScene() {
	// 第一视角初始位置
	x = 64;
	y = 10;
	z = 64;

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	snowman_display_list = createSnowman();

}

void render_scene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (int i = 0; i < 2; i++)
	for (int j = 0; j < 2; j++) {
		glPushMatrix();
		glTranslatef(70.0, 0, 70.0);
		glTranslatef(i*10.0, 0, j * 10.0);
		glCallList(snowman_display_list);
		
		glPopMatrix();
	}
	render_height_map();
	render_wall();
	render_sky();

	render_tree();


	if (glutGetWindow() != main_window)
		glutSetWindow(main_window);
	glutPostRedisplay();

	glutSwapBuffers();
}


void control_cb(int control) {
	printf("callback: %d\n", control);
	switch (control) {
	case TERRAIN_HIGHER_BUTTON_ID:
		set_terrain_height(1);
		break;
	case TERRAIN_LOWER_BUTTON_ID:
		set_terrain_height(-1);
		break;
	case TERRAIN_SAVE_BUTTON_ID:
		terrain_save();
		break;
	}
}



int main(int argc, char** argv) {
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(WINDOW_POS_X, WINDOW_POS_Y);
	glutInitWindowSize(WINDOW_LENGTH, WINDOW_WIDTH);
	main_window = glutCreateWindow("World Of Garden");

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
	initScene();

	initMapTexture();
	initTerran();

	glutReshapeFunc(reshape_init);
	glutDisplayFunc(render_scene);
	//glutIdleFunc(render_scene);


	// GLUI模块
	UI->glui = GLUI_Master.create_glui("GLUI", 0, WINDOW_LENGTH + WINDOW_POS_X + 15, WINDOW_POS_Y);
	UI->panel_terrain = UI->glui->add_panel("Terrain");
	UI->panel_plant = UI->glui->add_panel("Plant");
	UI->terrain_x = UI->glui->add_statictext_to_panel(UI->panel_terrain, "terrain x: -");
	UI->terrain_z = UI->glui->add_statictext_to_panel(UI->panel_terrain, "terrain z: -");
	UI->terrain_height_text = UI->glui->add_statictext_to_panel(UI->panel_terrain, "terrain height: -");
	UI->terrain_height_plus = UI->glui->add_button_to_panel(UI->panel_terrain, "Higher", TERRAIN_HIGHER_BUTTON_ID, control_cb);
	UI->terrain_height_dec = UI->glui->add_button_to_panel(UI->panel_terrain, "Lower", TERRAIN_LOWER_BUTTON_ID, control_cb);
	UI->terrain_save = UI->glui->add_button_to_panel(UI->panel_terrain, "Save", TERRAIN_SAVE_BUTTON_ID, control_cb);



	/*
	GLUI_Checkbox* t1 = UI->glui->add_checkbox("Click me", (int*)0, -1, control_cb);
	GLUI_Panel* p1 = glui->add_panel("123");
	glui->add_checkbox_to_panel(p1, "asd");d
	glui->add_checkbox("Click me");
	glui->add_checkbox("Click me");
	glui->add_checkbox("Click me");
	glui->add_checkbox("Click me");
	glui->add_checkbox("Click me");
	glui->add_checkbox("Click me");
	t1->set_name("asd");*/





	UI->glui->set_main_gfx_window(main_window);
	GLUI_Master.set_glutIdleFunc(render_scene);
	

	glutMainLoop();
	return 0;
}

