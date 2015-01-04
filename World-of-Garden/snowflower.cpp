#include "snowflower.h"

vector<Snow_flower> snow_flower;

Snow_flower::Snow_flower(int _x, int _z, SnowFlowerType _type, float _size)
{
	pos_x = _x;
	pos_z = _z;
	type = _type;
	size = _size;
	action_1 = false;
	action_count_1 = 0;
}

void Snow_flower::render()
{
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glPushMatrix();
	glTranslatef(4 * pos_x + 2, 0, 4 * pos_z + 2);

	// 花杆
	glColor3f(0.3f, 0.8f, 0.3f);
	glRotatef(270, 1, 0, 0);
	GLUquadric *qObj = gluNewQuadric();
	gluCylinder(qObj, 0.05f*size, 0.05f*size, 3.0f*size, 10, 10);
	glRotatef(90, 1, 0, 0);

	// 右叶子
	glColor3f(0.3f, 1.0f, 0.3f);
	GLfloat rightLeaf[3][3][3] = { {
		{ 0.0f*size, 1.5f, 0.0f*size },
	{ 1.0f*size, 1.5f, 1.0f*size },
	{ 2.0f*size, 2.0f, 0.0f*size } },

	{ { 0.0f*size, 1.5f*size, 0.0f*size },
	{ 1.0f*size, 1.5f*size, 0.0f*size },
	{ 2.0f*size, 2.0f*size, 0.0f*size } },

	{ { 0.0f*size, 1.5f*size, 0.0f*size },
	{ 1.0f*size, 1.5f*size, -1.0f*size },
	{ 2.0f*size, 2.0f*size, 0.0f*size } } };

	glMap2f(GL_MAP2_VERTEX_3, 0.0f, 10.0f, 3, 3, 0.0f, 10.0f, 9, 3, &rightLeaf[0][0][0]); 
	glMapGrid2f(10, 0.0f, 10.0f, 10, 0.0f, 10.0f);
	glEvalMesh2(GL_FILL, 0, 10, 0, 10);

	// 左叶子
	GLfloat leftLeaf[3][3][3] = { {
	{ 0.0f*size, 1.5f*size, 0.0f*size },
	{ -1.0f*size, 1.5f*size, -1.0f*size },
	{ -2.0f*size, 2.0f*size, 0.0f*size } },

	{ { 0.0f*size, 1.5f*size, 0.0f*size },
	{ -1.0f*size, 1.5f*size, 0.0f*size },
	{ -2.0f*size, 2.0f*size, 0.0f*size } },

	{ { 0.0f*size, 1.5f*size, 0.0f*size },
	{ -1.0f*size, 1.5f*size, 1.0f*size },
	{ -2.0f*size, 2.0f*size, 0.0f*size } } };

	glMap2f(GL_MAP2_VERTEX_3, 0.0f, 10.0f, 3, 3, 0.0f, 10.0f, 9, 3, &leftLeaf[0][0][0]);
	glMapGrid2f(10, 0.0f, 10.0f, 10, 0.0f, 10.0f);
	glEvalMesh2(GL_FILL, 0, 10, 0, 10);


	// 花瓣
	// 静止情况
	//if (action_1 = false) {
		for (int i = 0; i < 6; i++) {
			glColor3f(1.0f, 0.6f, 0.0f);
			GLfloat petal1[3][3][3] = { {
				{ 0.0f*size, 3.0f*size, 0.0f*size },
				{ -1.0f*size, 3.5f*size, -1.5f*size },
				{ -2.0f*size, 2.5f*size, 0.0f*size } },

				{ { 0.0f*size, 3.0f*size, 0.0f*size },
				{ -1.0f*size, 3.5f*size, 0.0f*size },
				{ -2.0f*size, 2.5f*size, 0.0f*size } },

				{ { 0.0f*size, 3.0f*size, 0.0f*size },
				{ -1.0f*size, 3.5f*size, 1.5f*size },
				{ -2.0f*size, 2.5f*size, 0.0f*size } } };
			glMap2f(GL_MAP2_VERTEX_3, 0.0f, 10.0f, 3, 3, 0.0f, 10.0f, 9, 3, &petal1[0][0][0]);
			glMapGrid2f(10, 0.0f, 10.0f, 10, 0.0f, 10.0f);
			glEvalMesh2(GL_FILL, 0, 10, 0, 10);
			glRotatef(60, 0, 1, 0);
		}
	//}
	/*
	// 抖动效果
	else {
		for (int i = 0; i < 6; i++) {
			if (action_count_1 < SNOWFLOWER_COLLAPSE_ACTION / 2) {
				glColor3f(1.0f, 0.6f, 0.0f);
				GLfloat petal1[3][3][3] = { {
					{ 0.0f*size, 3.0f*size, 0.0f*size },
					{ -1.0f*size + action_count_1/60*size, 3.5f*size, -1.5f*size },
					{ -2.0f*size + action_count_1/30*size, 2.5f*size, 0.0f*size } },

					{ { 0.0f*size, 3.0f*size, 0.0f*size },
					{ -1.0f*size + action_count_1 / 60 * size, 3.5f*size, 0.0f*size },
					{ -2.0f*size + action_count_1 / 30 * size, 2.5f*size, 0.0f*size } },

					{ { 0.0f*size, 3.0f*size, 0.0f*size },
					{ -1.0f*size + action_count_1 / 60 * size, 3.5f*size, 1.5f*size },
					{ -2.0f*size + action_count_1 / 30 * size, 2.5f*size, 0.0f*size } } };
				glMap2f(GL_MAP2_VERTEX_3, 0.0f, 10.0f, 3, 3, 0.0f, 10.0f, 9, 3, &petal1[0][0][0]);
				glMapGrid2f(10, 0.0f, 10.0f, 10, 0.0f, 10.0f);
				glEvalMesh2(GL_FILL, 0, 10, 0, 10);
				glRotatef(60, 0, 1, 0);
			}
			else {
				glColor3f(1.0f, 0.6f, 0.0f);
				GLfloat petal1[3][3][3] = { {
					{ 0.0f*size, 3.0f*size, 0.0f*size },
					{ -1.0f*size + (SNOWFLOWER_COLLAPSE_ACTION-action_count_1) / 60 * size, 3.5f*size, -1.5f*size },
					{ -2.0f*size + (SNOWFLOWER_COLLAPSE_ACTION - action_count_1) / 30 * size, 2.5f*size, 0.0f*size } },

					{ { 0.0f*size, 3.0f*size, 0.0f*size },
					{ -1.0f*size + (SNOWFLOWER_COLLAPSE_ACTION - action_count_1) / 60 * size, 3.5f*size, 0.0f*size },
					{ -2.0f*size + (SNOWFLOWER_COLLAPSE_ACTION - action_count_1) / 30, 2.5f*size, 0.0f*size } },

					{ { 0.0f*size, 3.0f*size, 0.0f*size },
					{ -1.0f*size + (SNOWFLOWER_COLLAPSE_ACTION - action_count_1) / 60 * size, 3.5f*size, 1.5f*size },
					{ -2.0f*size + (SNOWFLOWER_COLLAPSE_ACTION - action_count_1) / 30 * size, 2.5f*size, 0.0f*size } } };
				glMap2f(GL_MAP2_VERTEX_3, 0.0f, 10.0f, 3, 3, 0.0f, 10.0f, 9, 3, &petal1[0][0][0]);
				glMapGrid2f(10, 0.0f, 10.0f, 10, 0.0f, 10.0f);
				glEvalMesh2(GL_FILL, 0, 10, 0, 10);
				glRotatef(60, 0, 1, 0);
			}
		}

		action_count_1++;
		if (action_count_1 >= SNOWFLOWER_COLLAPSE_ACTION) {
			action_1 = false;
			action_count_1 = 0;
		}
	}
	*/
	
	

	

	glPopMatrix();
}

void Snow_flower::collapse_snow_flower_level_1()
{
	for (unsigned i = 0; i < particle_set_1.size(); i++) {
		((Particle*)particle_set_1[i])->attach = false;
	}
	particle_set_1.clear();
	action_1 = true;
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
		snow_flower[i].particle_set_1.clear();
		snow_flower[i].action_1 = true;
	}

}