#include "snowplant.h"

vector<Snow_plant> snow_plant;


Snow_plant::Snow_plant(int _x, int _z, SnowPlantType _type)
{
	pos_x = _x;
	pos_z = _z;
	type = _type;
}



void Snow_plant::render()
{
	glPushMatrix();
	glTranslatef(4*pos_x + 2, 1, 4*pos_z + 2);
	

	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidSphere(0.5f, 6, 6);



	glPopMatrix();

}






void initSnowplant()
{
	Snow_plant temp_0(21, 20, SnowPlantType::XTREE);
	snow_plant.push_back(temp_0);
}

void render_snow_plant()
{
	for (unsigned i = 0; i < snow_plant.size(); i++) {
		snow_plant[i].render();
	}
}