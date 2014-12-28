#ifndef SNOWPLANTH
#define SNOWPLANTH

#include <vector>
#include "plants.h"
#include "map.h"
#include "glhead.h"

using std::vector;

enum SnowPlantType{XTREE};


class Snow_plant {

public:
	Snow_plant(int _x, int _z, SnowPlantType _type);
	void render();


private:
	int pos_x;
	int pos_z;
	float size;
	SnowPlantType type;

};

void initSnowplant();
void render_snow_plant();


#endif