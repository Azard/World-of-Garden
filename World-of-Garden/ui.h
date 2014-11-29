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
#define PLANT_LEVEL_PLUS_BUTTON_ID 4
#define PLANT_LEVEL_DEC_BUTTON_ID 5
#define PLANT_SAVE_BUTTON_ID 6
#define PLANT_CREATE_TREE_BUTTON_ID 7
#define PLANT_CREATE_FLOWER_BUTTON_ID 8
#define PLANT_DELETE_BUTTON_ID 9
#define PLANT_CHANGE_HEIGHT_BUTTON_ID 10
#define PLANT_CHANGE_BIG_R_BUTTON_ID 11
#define PLANT_CHANGE_SMALL_R_BUTTON_ID 12
#define PLANT_CHANGE_LEAF_NUM_BUTTON_ID 13
#define PLANT_CHANGE_LEAF_SIZE_BUTTON_ID 14
#define PLANT_CHANGE_LEAF_TYPE_BUTTON_ID 15
#define PLANT_CHANGE_COLOR_BUTTON_ID 16

struct UI_set {
	GLUI* glui;
	GLUI_Panel* panel_terrain;
	GLUI_Panel* panel_plant;
	GLUI_Panel* panel_data;

	GLUI_StaticText* terrain_x;
	GLUI_StaticText* terrain_z;
	GLUI_StaticText* terrain_height_text;
	GLUI_Button* terrain_height_plus;
	GLUI_Button* terrain_height_dec;
	GLUI_Button* terrain_save;

	GLUI_StaticText* plant_type;
	GLUI_StaticText* plant_x;
	GLUI_StaticText* plant_z;
	GLUI_EditText* plant_edit_height;
	GLUI_Panel* plant_level_panel;
	GLUI_StaticText* plant_level;
	GLUI_Panel* plant_height_panel;
	GLUI_StaticText* plant_height;
	GLUI_StaticText* plant_big_radius;
	GLUI_StaticText* plant_small_radius;
	GLUI_StaticText* plant_leaf_num;
	GLUI_StaticText* plant_leaf_size;
	GLUI_StaticText* plant_leaf_type;
	GLUI_StaticText* plant_flower_color_r;
	GLUI_StaticText* plant_flower_color_g;
	GLUI_StaticText* plant_flower_color_b;

	GLUI_Panel* plant_create_panel;
	GLUI_Button* plant_create_tree;
	GLUI_Button* plant_create_flower;
	GLUI_Button* plant_delete;
	GLUI_Button* plant_level_plus;
	GLUI_Button* plant_level_dec;
	GLUI_Button* plant_change_height;

	GLUI_Panel* plant_r_panel;
	GLUI_EditText* plant_edit_big_r;
	GLUI_EditText* plant_edit_small_r;
	GLUI_Button* plant_change_big_r;
	GLUI_Button* plant_change_small_r;

	GLUI_Panel* plant_leaf_panel;
	GLUI_EditText* plant_edit_leaf_num;
	GLUI_Button* plant_leaf_num_button;
	GLUI_EditText* plant_edit_leaf_size;
	GLUI_Button* plant_leaf_size_button;
	GLUI_Listbox* plant_list_leaf_type;
	GLUI_Button* plant_leaf_type_button;

	GLUI_Panel* plant_color_panel;
	GLUI_EditText* plant_edit_color_r;
	GLUI_EditText* plant_edit_color_g;
	GLUI_EditText* plant_edit_color_b;
	GLUI_Button* plant_color_button;


	GLUI_Button* plant_save;

};

#endif