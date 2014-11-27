#ifndef UIH
#define UIH

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/glui.h>

#define TERRAIN_HIGHER_BUTTON_ID 1
#define TERRAIN_LOWER_BUTTON_ID 2
#define TERRAIN_SAVE_BUTTON_ID 3

struct UI_set {
	GLUI* glui;
	GLUI_Panel* panel_terrain;
	GLUI_Panel* panel_plant;

	GLUI_StaticText* terrain_x;
	GLUI_StaticText* terrain_z;
	GLUI_StaticText* terrain_height_text;
	GLUI_Button* terrain_height_plus;
	GLUI_Button* terrain_height_dec;
	GLUI_Button* terrain_save;

	GLUI_StaticText* plant_type;
	GLUI_StaticText* plant_x;
	GLUI_StaticText* plant_z;
	GLUI_Panel* plant_level_panel;
	GLUI_StaticText* plant_level;
	GLUI_Button* plant_level_plus;
	GLUI_Button* plant_level_dec;

};

#endif