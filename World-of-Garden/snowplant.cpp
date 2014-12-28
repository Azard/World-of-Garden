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
	glTranslatef(4*pos_x + 2, 0, 4*pos_z + 2);
	
	glColor3f(0.8f, 0.7f, 0.5f);
	glRotatef(270, 1, 0, 0);
	GLUquadric *qObj = gluNewQuadric();
	gluCylinder(qObj, 0.2f, 0.0f, 5.0f, CYLINDER_SLICES, CYLINDER_STACKS);


	glRotatef(90, 1, 0, 0);
	glTranslatef(0, 4.0f, 0);
	glRotatef(270, 1, 0, 0);
	glColor3f(0.1f, 0.7f, 0.1f);
	GLUquadric *qObj2 = gluNewQuadric();
	gluCylinder(qObj2, 1.0f, 0, 1.0f, CYLINDER_SLICES, CYLINDER_STACKS);
	



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