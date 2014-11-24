#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/GLAUX.H>


#define CYLINDER_SLICES 20
#define CYLINDER_STACKS 20


struct tree_leaf {
	int num;
	float size;
	int type;
};

void render_tree();
void draw_tree_main(int x, int y);