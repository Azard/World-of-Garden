#ifndef SNOWFLOWERH
#define SNOWFLOWERH

#include <vector>
#include "plants.h"
#include "map.h"
#include "particle.h"
#include "glhead.h"

#define SNOWFLOWER_COLLAPSE_MAX 6
#define SNOWFLOWER_COLLAPSE_ACTION 60

using std::vector;

enum SnowFlowerType{NFLOWER};

class Snow_flower {
public:
	Snow_flower(int _x, int _z, SnowFlowerType _type, float _size);
	void render();
	void collapse_snow_flower_level_1();

	int pos_x;  // center_x: 4*pos_x + 2
	int pos_z;	// center_z: 4*pos_z + 2
	float size;
	SnowFlowerType type;
	bool action_1;
	int action_count_1;
	vector<void*> particle_set_1;	// ª®…œ

private:
};

void initSnowflower();
void render_snow_flower();
void collapse_snow_flower();

extern vector<Snow_flower> snow_flower;


#endif