#include "snowplant.h"

vector<Snow_plant> snow_plant;


Snow_plant::Snow_plant(int _x, int _z, SnowPlantType _type, float _size)
{
	pos_x = _x;
	pos_z = _z;
	type = _type;
	size = _size;
}



void Snow_plant::render()
{
	glPushMatrix();
	glTranslatef(4*pos_x + 2, 0, 4*pos_z + 2);
	
	// 树干
	glColor3f(0.8f, 0.7f, 0.5f);
	glRotatef(270, 1, 0, 0);
	GLUquadric *qObj = gluNewQuadric();
	gluCylinder(qObj, 0.4f*size, 0.0f, 8.0f*size, CYLINDER_SLICES, CYLINDER_STACKS);
	glRotatef(90, 1, 0, 0);
	
	// 第一层
	glTranslatef(0, 6.5f*size, 0);
	glRotatef(270, 1, 0, 0);
	glColor3f(0.1f, 0.7f, 0.1f);
	GLUquadric *qObj2 = gluNewQuadric();
	gluCylinder(qObj2, 1.5f*size, 0, 1.5f*size, CYLINDER_SLICES, CYLINDER_STACKS);
	glRotatef(90, 1, 0, 0);

	// 第二层
	glTranslatef(0, -1.7f*size, 0);
	glRotatef(270, 1, 0, 0);
	glColor3f(0.1f, 0.7f, 0.1f);
	GLUquadric *qObj3 = gluNewQuadric();
	gluCylinder(qObj3, 2.2f*size, 0, 2.2f*size, CYLINDER_SLICES, CYLINDER_STACKS);
	glRotatef(90, 1, 0, 0);

	// 第三层
	glTranslatef(0, -2.3f*size, 0);
	glRotatef(270, 1, 0, 0);
	glColor3f(0.1f, 0.7f, 0.1f);
	GLUquadric *qObj4 = gluNewQuadric();
	gluCylinder(qObj4, 3.0f*size, 0, 3.0f*size, CYLINDER_SLICES, CYLINDER_STACKS);
	glRotatef(90, 1, 0, 0);

	glPopMatrix();
}

void Snow_plant::collapse_snow_plant_level_1()
{
	for (unsigned i = 0; i < particle_set_1.size(); i++) {
		((Particle*)particle_set_1[i])->attach = false;
	}
	particle_set_1.clear();
}

void Snow_plant::collapse_snow_plant_level_2()
{
	for (unsigned i = 0; i < particle_set_2.size(); i++) {
		((Particle*)particle_set_2[i])->attach = false;
	}
	particle_set_2.clear();
}

void Snow_plant::collapse_snow_plant_level_3()
{
	for (unsigned i = 0; i < particle_set_3.size(); i++) {
		((Particle*)particle_set_3[i])->attach = false;
	}
	particle_set_3.clear();
}



void initSnowplant()
{
	Snow_plant temp_0(21, 17, SnowPlantType::XTREE, 1.0f);
	snow_plant.push_back(temp_0);
	Snow_plant temp_1(19, 18, SnowPlantType::XTREE, 0.8f);
	snow_plant.push_back(temp_1);
}

void render_snow_plant()
{
	for (unsigned i = 0; i < snow_plant.size(); i++) {
		snow_plant[i].render();
	}
}

void collapse_snow_plant()
{
	for (unsigned i = 0; i < snow_plant.size(); i++) {
		for (unsigned j = 0; j < snow_plant[i].particle_set_1.size(); j++) {
			((Particle*)snow_plant[i].particle_set_1[j])->attach = false;
		}
		for (unsigned j = 0; j < snow_plant[i].particle_set_2.size(); j++) {
			((Particle*)snow_plant[i].particle_set_2[j])->attach = false;
		}
		for (unsigned j = 0; j < snow_plant[i].particle_set_3.size(); j++) {
			((Particle*)snow_plant[i].particle_set_3[j])->attach = false;
		}
		snow_plant[i].particle_set_1.clear();
		snow_plant[i].particle_set_2.clear();
		snow_plant[i].particle_set_3.clear();
	}
	
}