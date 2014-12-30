#ifndef SNOWPLANTH
#define SNOWPLANTH

#include <vector>
#include "plants.h"
#include "map.h"
#include "particle.h"
#include "glhead.h"

using std::vector;

enum SnowPlantType{XTREE};


class Snow_plant {
public:
	Snow_plant(int _x, int _z, SnowPlantType _type);
	void render();

	int pos_x;  // center_x: 4*pos_x + 2
	int pos_z;	// center_z: 4*pos_z + 2
	float size;
	SnowPlantType type;
	vector<void*> particle_set_1;	// µÚÒ»²ã»ýÑ©
	vector<void*> particle_set_2;
	vector<void*> particle_set_3;

private:

};

void initSnowplant();
void render_snow_plant();
void collapse_snow_plant();

extern vector<Snow_plant> snow_plant;


#endif