#ifndef MAPH
#define MAPH
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "keyboard.h"
#include "particle.h"
#include "glhead.h"

#define MAP_SIZE		128
#define STEP_SIZE		4
#define HEIGHT_RATIO	10.0f
#define TEXTURE_NUM		16
#define TRY_DEC_TIMES	5

#define MAX_SPOT_PER_TERRAIN 10
#define SPOT_PER_HEIGHT 10
#define SNOW_ADD_HEIGHT 1

struct Spot_pos {
	float x;
	float z;
};


class Terrain_snow {
public:
	Terrain_snow();
	~Terrain_snow();
	void add_spot(float pos_x,float pos_z);
	//bool is_accumulation();
	
	int spot_count;
	//Spot_pos spot_set[MAX_SPOT_PER_TERRAIN];


private:
	


};

extern GLuint texture[TEXTURE_NUM];
extern Terrain_snow* snow_spot;

void thawSnow();
void load_terran();
void render_height_map();
void render_wall();
void render_sky();
void render_moon();
int get_terran_height(int x, int y);
void set_terrain_height(int height_plus);
void terrain_save();
void initTerran();

AUX_RGBImageRec* LoadBMP(char *Filename);
int LoadGLTextures();
void initMapTexture();


#endif