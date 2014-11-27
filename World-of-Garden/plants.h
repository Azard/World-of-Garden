#ifndef PLANTSH
#define PLANTSH

#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/GLAUX.H>


#define PLANT_NUM		31
#define CYLINDER_SLICES 20
#define CYLINDER_STACKS 20

enum {PLANT_TYPE_NONE, PLANT_TYPE_TREE, PLANT_TYPE_FLOWER};
enum {TREE_LEAF_TRIANGLE};



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


};


struct tree_leaf {
	int num;
	float size;
	int type;
};


void initPlant();
void savePlant();
void readPlant();
void render_tree();
void draw_tree_main(plant p);

#endif