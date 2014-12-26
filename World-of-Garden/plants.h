#ifndef PLANTSH
#define PLANTSH

#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include "glhead.h"
#include "map.h"

#define PLANT_NUM		31
#define CYLINDER_SLICES 20
#define CYLINDER_STACKS 20

enum {PLANT_TYPE_NONE, PLANT_TYPE_TREE, PLANT_TYPE_FLOWER};
enum {TREE_LEAF_PINE=1, TREE_LEAF_SAKURA};
enum {FLOWER_NORMAL=1, FLOWER_SUN};

struct plant {
	int plant_type;
	int map_X; // map_X 0 is translate to 2, 1 is translate to 6
	int map_Z;

	int tree_level;
	float tree_height;
	float tree_big_r;
	float tree_little_r;
	int tree_leaf_num;
	float tree_leaf_size;
	int tree_leaf_type;

	int flower_color_r;
	int flower_color_g;
	int flower_color_b;
};



void initPlant();
void savePlant();
void readPlant();
void render_plant();
void draw_tree_main(plant p);
void draw_flower_main(plant p);

void select_flush_ui();


void ops_delete_plant();
void ops_create_tree();
void ops_create_flower();
void ops_tree_level(int delta);
void ops_tree_height(std::string input);
void ops_tree_big_radius(std::string input);
void ops_tree_small_radius(std::string input);
void ops_tree_leaf_num(std::string input);
void ops_tree_leaf_size(std::string input);
void ops_tree_leaf_type(int input);
void ops_flower_color(std::string r, std::string g, std::string b);


#endif