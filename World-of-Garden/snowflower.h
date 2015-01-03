#ifndef SNOWFLOWERH
#define SNOWFLOWERH

#include <vector>
#include "plants.h"
#include "map.h"
#include "particle.h"
#include "glhead.h"

using std::vector;

enum SnowFlowerType{NFLOWER};

class Snow_flower {
public:
	Snow_flower(int _x, int _z, SnowFlowerType _type, float _size);
	void render();

	int pos_x;  // center_x: 4*pos_x + 2
	int pos_z;	// center_z: 4*pos_z + 2
	float size;
	SnowFlowerType type;
	vector<void*> particle_set_1;	// ª®…œ

private:
};

void initSnowflower();
void render_snow_flower();
void collapse_snow_flower();

extern vector<Snow_flower> snow_flower;


#endif