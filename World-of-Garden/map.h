#ifndef MAPH
#define MAPH
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <GL/glut.h>
#include <GL/GLAUX.H>
#include "keyboard.h"

#define MAP_SIZE		128
#define STEP_SIZE		4
#define HEIGHT_RATIO	10.0f
#define TEXTURE_NUM		2



void load_terran();
void render_height_map();
void render_wall();
void render_sky();
int get_terran_height(int x, int y);
void set_terrain_height(int height_plus);
void terrain_save();
void initTerran();

AUX_RGBImageRec* LoadBMP(char *Filename);
int LoadGLTextures();
void initMapTexture();


#endif