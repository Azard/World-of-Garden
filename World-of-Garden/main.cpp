//#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )

#define GLUT_DISABLE_ATEXIT_HACK

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/glui.h>
#include <Windows.h>
#include "keyboard.h"
#include "mouse.h"
#include "map.h"
#include "plants.h"
#include "ui.h"

#define WINDOW_POS_X	0
#define WINDOW_POS_Y	0
#define WINDOW_LENGTH	1024
#define WINDOW_WIDTH	768

GLint snowman_display_list;
int main_window;
UI_set* UI = new UI_set;
int frame = 0, time = 0, timebase = 0, fps;

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
	x = 90;
	y = 5;
	z = 90;

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	snowman_display_list = createSnowman();
}

void initLight() {
	GLfloat ambientLight[] = { 0.6f, 0.6f, 0.6f, 1.0f };//白色主光源环境光  
	GLfloat diffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };//白色主光源漫反射  
	GLfloat specularLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };//白色主光源镜面光  

	GLfloat lightPos[] = { 50.0f, 10.0f, 50.0f, 1.0f };  //光源位置  

	glEnable(GL_LIGHTING);                          //启用光照  
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);   //设置环境光源  
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);   //设置漫反射光源  
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight); //设置镜面光源  
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);      //设置灯光位置  
	glEnable(GL_LIGHT0);                            //打开白色主光源  

	glEnable(GL_COLOR_MATERIAL);                        //启用材质的颜色跟踪  
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);   //指定材料着色的面  
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularLight);   //指定材料对镜面光的反应  
	glMateriali(GL_FRONT, GL_SHININESS, 100);             //指定反射系数  
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
	render_plant();


	if (glutGetWindow() != main_window)
		glutSetWindow(main_window);
	glutPostRedisplay();

	glutSwapBuffers();


	// 计算输出fps
	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		fps = frame*1000.0 / (time - timebase);
		timebase = time;
		frame = 0;
		printf("fps: %d\n", fps);
	}
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
	case PLANT_LEVEL_PLUS_BUTTON_ID:
		ops_tree_level(1);
		break;
	case PLANT_LEVEL_DEC_BUTTON_ID:
		ops_tree_level(-1);
		break;
	case PLANT_SAVE_BUTTON_ID:
		savePlant();
		break;
	case PLANT_CREATE_TREE_BUTTON_ID:
		ops_create_tree();
		break;;
	case PLANT_CREATE_FLOWER_BUTTON_ID:
		ops_create_flower();
		break;
	case PLANT_DELETE_BUTTON_ID:
		ops_delete_plant();
		break;
	case PLANT_CHANGE_HEIGHT_BUTTON_ID:
		ops_tree_height(std::string(UI->plant_edit_height->get_text()));
		break;
	case PLANT_CHANGE_BIG_R_BUTTON_ID:
		ops_tree_big_radius(std::string(UI->plant_edit_big_r->get_text()));
		break;
	case PLANT_CHANGE_SMALL_R_BUTTON_ID:
		ops_tree_small_radius(std::string(UI->plant_edit_small_r->get_text()));
		break;
	case PLANT_CHANGE_LEAF_NUM_BUTTON_ID:
		ops_tree_leaf_num(std::string(UI->plant_edit_leaf_num->get_text()));
		break;
	case PLANT_CHANGE_LEAF_SIZE_BUTTON_ID:
		ops_tree_leaf_size(std::string(UI->plant_edit_leaf_size->get_text()));
		break;
	case PLANT_CHANGE_LEAF_TYPE_BUTTON_ID:
		ops_tree_leaf_type(UI->plant_list_leaf_type->get_int_val());
		break;
	case PLANT_CHANGE_COLOR_BUTTON_ID:
		ops_flower_color(UI->plant_edit_color_r->get_text(), UI->plant_edit_color_g->get_text(), UI->plant_edit_color_b->get_text());
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
	initPlant();

	initMapTexture();
	initTerran();
	initLight();

	glutReshapeFunc(reshape_init);
	glutDisplayFunc(render_scene);
	//glutIdleFunc(render_scene);




	// GLUI terrain部分
	UI->glui = GLUI_Master.create_glui("GLUI", 0, WINDOW_LENGTH + WINDOW_POS_X + 15, WINDOW_POS_Y);
	UI->panel_terrain = UI->glui->add_panel("Terrain");
	UI->panel_plant = UI->glui->add_panel("Plant");

	UI->terrain_x = UI->glui->add_statictext_to_panel(UI->panel_terrain, "terrain x: -");
	UI->terrain_z = UI->glui->add_statictext_to_panel(UI->panel_terrain, "terrain z: -");
	UI->terrain_height_text = UI->glui->add_statictext_to_panel(UI->panel_terrain, "terrain height: -");
	UI->glui->add_column_to_panel(UI->panel_terrain);
	UI->terrain_height_plus = UI->glui->add_button_to_panel(UI->panel_terrain, "Higher", TERRAIN_HIGHER_BUTTON_ID, control_cb);
	UI->terrain_height_dec = UI->glui->add_button_to_panel(UI->panel_terrain, "Lower", TERRAIN_LOWER_BUTTON_ID, control_cb);
	UI->terrain_save = UI->glui->add_button_to_panel(UI->panel_terrain, "Save", TERRAIN_SAVE_BUTTON_ID, control_cb);

	// GLUI plant部分
	UI->panel_data = UI->glui->add_panel_to_panel(UI->panel_plant, "data");
	UI->plant_type = UI->glui->add_statictext_to_panel(UI->panel_data, "plant type: -");
	UI->plant_x = UI->glui->add_statictext_to_panel(UI->panel_data, "plant x: -");
	UI->plant_z = UI->glui->add_statictext_to_panel(UI->panel_data, "plant z: -");
	UI->plant_level = UI->glui->add_statictext_to_panel(UI->panel_data, "plant level: -");
	UI->plant_height = UI->glui->add_statictext_to_panel(UI->panel_data, "plant height: -");
	UI->plant_big_radius = UI->glui->add_statictext_to_panel(UI->panel_data, "plant big r: -");
	UI->plant_small_radius = UI->glui->add_statictext_to_panel(UI->panel_data, "plant small r: -");
	UI->glui->add_column_to_panel(UI->panel_data);
	UI->plant_leaf_num = UI->glui->add_statictext_to_panel(UI->panel_data, "leaf number: -");
	UI->plant_leaf_size = UI->glui->add_statictext_to_panel(UI->panel_data, "leaf size: -");
	UI->plant_leaf_type = UI->glui->add_statictext_to_panel(UI->panel_data, "leaf type: -");
	UI->plant_flower_color_r = UI->glui->add_statictext_to_panel(UI->panel_data, "color r: -");
	UI->plant_flower_color_g = UI->glui->add_statictext_to_panel(UI->panel_data, "color g: -");
	UI->plant_flower_color_b = UI->glui->add_statictext_to_panel(UI->panel_data, "color b: -");
	

	UI->plant_delete = UI->glui->add_button_to_panel(UI->panel_plant, "Delete", PLANT_DELETE_BUTTON_ID, control_cb);

	// Create Panel
	UI->plant_create_panel = UI->glui->add_panel_to_panel(UI->panel_plant, "create");
	UI->plant_create_tree = UI->glui->add_button_to_panel(UI->plant_create_panel, "create tree", PLANT_CREATE_TREE_BUTTON_ID, control_cb);
	UI->glui->add_column_to_panel(UI->plant_create_panel, true);
	UI->plant_create_flower = UI->glui->add_button_to_panel(UI->plant_create_panel, "create flower", PLANT_CREATE_FLOWER_BUTTON_ID, control_cb);

	// Level panel
	UI->plant_level_panel = UI->glui->add_panel_to_panel(UI->panel_plant, "level option");
	UI->plant_level_plus = UI->glui->add_button_to_panel(UI->plant_level_panel, "level plus", PLANT_LEVEL_PLUS_BUTTON_ID, control_cb);
	UI->glui->add_column_to_panel(UI->plant_level_panel, true);
	UI->plant_level_dec = UI->glui->add_button_to_panel(UI->plant_level_panel, "level dec", PLANT_LEVEL_DEC_BUTTON_ID, control_cb);

	//Height panel
	UI->plant_height_panel = UI->glui->add_panel_to_panel(UI->panel_plant, "change height");
	UI->plant_edit_height = UI->glui->add_edittext_to_panel(UI->plant_height_panel, "height:");
	UI->glui->add_column_to_panel(UI->plant_height_panel);
	UI->plant_change_height = UI->glui->add_button_to_panel(UI->plant_height_panel, "change", PLANT_CHANGE_HEIGHT_BUTTON_ID, control_cb);

	// radius panel
	UI->plant_r_panel = UI->glui->add_panel_to_panel(UI->panel_plant, "radius option");
	UI->plant_edit_big_r = UI->glui->add_edittext_to_panel(UI->plant_r_panel, "big    radius:");
	UI->plant_edit_small_r = UI->glui->add_edittext_to_panel(UI->plant_r_panel, "small radius:");
	UI->glui->add_column_to_panel(UI->plant_r_panel);
	UI->plant_change_big_r = UI->glui->add_button_to_panel(UI->plant_r_panel, "change", PLANT_CHANGE_BIG_R_BUTTON_ID, control_cb);
	UI->plant_change_small_r = UI->glui->add_button_to_panel(UI->plant_r_panel, "change", PLANT_CHANGE_SMALL_R_BUTTON_ID, control_cb);

	// leaf panel
	UI->plant_leaf_panel = UI->glui->add_panel_to_panel(UI->panel_plant, "leaf option");
	UI->plant_edit_leaf_num = UI->glui->add_edittext_to_panel(UI->plant_leaf_panel, "number:");
	UI->plant_edit_leaf_size = UI->glui->add_edittext_to_panel(UI->plant_leaf_panel, "size:");
	UI->plant_list_leaf_type = UI->glui->add_listbox_to_panel(UI->plant_leaf_panel, "        type:");
	UI->glui->add_column_to_panel(UI->plant_leaf_panel);
	UI->plant_leaf_num_button = UI->glui->add_button_to_panel(UI->plant_leaf_panel, "change", PLANT_CHANGE_LEAF_NUM_BUTTON_ID, control_cb);
	UI->plant_leaf_size_button = UI->glui->add_button_to_panel(UI->plant_leaf_panel, "change", PLANT_CHANGE_LEAF_SIZE_BUTTON_ID, control_cb);
	UI->plant_leaf_type_button = UI->glui->add_button_to_panel(UI->plant_leaf_panel, "change", PLANT_CHANGE_LEAF_TYPE_BUTTON_ID, control_cb);

	// rgb panel
	UI->plant_color_panel = UI->glui->add_panel_to_panel(UI->panel_plant, "color");
	UI->plant_edit_color_r = UI->glui->add_edittext_to_panel(UI->plant_color_panel, "R:");
	UI->plant_edit_color_g = UI->glui->add_edittext_to_panel(UI->plant_color_panel, "G:");
	UI->glui->add_column_to_panel(UI->plant_color_panel);
	UI->plant_edit_color_b = UI->glui->add_edittext_to_panel(UI->plant_color_panel, "B:");
	UI->plant_color_button = UI->glui->add_button_to_panel(UI->plant_color_panel, "change", PLANT_CHANGE_COLOR_BUTTON_ID, control_cb);


	// Save
	UI->plant_save = UI->glui->add_button_to_panel(UI->panel_plant, "Save", PLANT_SAVE_BUTTON_ID, control_cb);

	


	//savePlant();
	readPlant();
	
	


	UI->glui->set_main_gfx_window(main_window);
	GLUI_Master.set_glutIdleFunc(render_scene);
	

	glutMainLoop();
	return 0;
}

