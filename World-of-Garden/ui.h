#ifndef UIH
#define UIH

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/glui.h>


struct UI_set {
	GLUI* glui;
	GLUI_Panel* panel_terrain;
	GLUI_Panel* panel_plant;

	GLUI_StaticText* terrain_x;
	GLUI_StaticText* terrain_z;
	GLUI_StaticText* terrain_height_text;


};

#endif