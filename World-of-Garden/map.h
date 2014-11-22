#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>

#define MAP_SIZE		1024
#define STEP_SIZE		8
#define HEIGHT_RATIO	1.5f


void initTerran();
void load_terran();
void RenderHeightMap();
int get_terran_height(int x, int y);