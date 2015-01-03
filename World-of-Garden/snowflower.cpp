#include "snowflower.h"

vector<Snow_flower> snow_flower;

Snow_flower::Snow_flower(int _x, int _z, SnowFlowerType _type, float _size)
{
	pos_x = _x;
	pos_z = _z;
	type = _type;
	size = _size;
}

void Snow_flower::render()
{
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glPushMatrix();
	glTranslatef(4 * pos_x + 2, 0, 4 * pos_z + 2);

	// »¨¸Ë
	glColor3f(0.3f, 0.8f, 0.3f);
	glRotatef(270, 1, 0, 0);
	GLUquadric *qObj = gluNewQuadric();
	gluCylinder(qObj, 0.05f*size, 0.05f*size, 3.0f*size, 10, 10);
	glRotatef(90, 1, 0, 0);

	// ÓÒÒ¶×Ó
	glColor3f(0.3f, 1.0f, 0.3f);
	GLfloat rightLeaf[3][3][3] = { {
	{ 0.0f, 2.0f, 0.0f },
	{ 1.0f, 2.0f, 1.0f },
	{ 2.0f, 2.5f, 0.0f } },

	{ { 0.0f, 2.0f, 0.0f },
	{ 1.0f, 2.0f, 0.0f },
	{ 2.0f, 2.5f, 0.0f } },

	{ { 0.0f, 2.0f, 0.0f },
	{ 1.0f, 2.0f, -1.0f },
	{ 2.0f, 2.5f, 0.0f } } };

	glMap2f(GL_MAP2_VERTEX_3, 0.0f, 10.0f, 3, 3, 0.0f, 10.0f, 9, 3, &rightLeaf[0][0][0]); 
	glMapGrid2f(10, 0.0f, 10.0f, 10, 0.0f, 10.0f);
	glEvalMesh2(GL_FILL, 0, 10, 0, 10);

	// ×óÒ¶×Ó
	GLfloat leftLeaf[3][3][3] = { {
	{ 0.0f, 2.0f, 0.0f },
	{ -1.0f, 2.0f, -1.0f },
	{ -2.0f, 2.5f, 0.0f } },

	{ { 0.0f, 2.0f, 0.0f },
	{ -1.0f, 2.0f, 0.0f },
	{ -2.0f, 2.5f, 0.0f } },

	{ { 0.0f, 2.0f, 0.0f },
	{ -1.0f, 2.0f, 1.0f },
	{ -2.0f, 2.5f, 0.0f } } };

	glMap2f(GL_MAP2_VERTEX_3, 0.0f, 10.0f, 3, 3, 0.0f, 10.0f, 9, 3, &leftLeaf[0][0][0]);
	glMapGrid2f(10, 0.0f, 10.0f, 10, 0.0f, 10.0f);
	glEvalMesh2(GL_FILL, 0, 10, 0, 10);

	




	glPopMatrix();
}



void initSnowflower()
{
	Snow_flower temp_0(21, 20, SnowFlowerType::NFLOWER, 1.0f);
	snow_flower.push_back(temp_0);
}

void render_snow_flower()
{
	for (unsigned i = 0; i < snow_flower.size(); i++) {
		snow_flower[i].render();
	}
}

void collapse_snow_flower()
{
	for (unsigned i = 0; i < snow_flower.size(); i++) {
		for (unsigned j = 0; j < snow_flower[i].particle_set_1.size(); j++) {
			((Particle*)snow_flower[i].particle_set_1[j])->attach = false;
		}
		for (unsigned j = 0; j < snow_flower[i].particle_set_2.size(); j++) {
			((Particle*)snow_flower[i].particle_set_2[j])->attach = false;
		}
	}
}