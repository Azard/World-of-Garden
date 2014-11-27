#include "plants.h"

std::fstream plant_stream;
plant* plant_data = new plant[PLANT_NUM * PLANT_NUM];



void draw_tree_leaf(int level, float height, plant p) {
	if (level <= 1)
		return;
	int num = p.tree_leaf_num;
	float size = p.tree_leaf_size;

	glBegin(GL_TRIANGLES);
	{
		glColor3f(0.1f, 0.7f, 0.1f);
		for (int i = 0; i < num; i++) {
			float t = height / num;
			glVertex3f(0, t * i, 0);
			glVertex3f(0, size + t * i, 0);
			glVertex3f(size, size + t * i, 0);
		}
	}
	glEnd();
}

void draw_tree_recursion(int level, float height, float radius, plant p) {
	if (level < 1) {
		return;
	}
	glColor3f(0.8f, 0.7f, 0.5f);
	GLUquadric *qObj = gluNewQuadric();
	glRotatef(270, 1, 0, 0);
	gluCylinder(qObj, radius, radius/2, height, CYLINDER_SLICES, CYLINDER_STACKS);
	glRotatef(90, 1, 0, 0);

	float child_height = height / 2;
	float child_radius = radius / 2;

	// 上面的树枝
	glPushMatrix();
		glTranslatef(0, height, 0);
		draw_tree_recursion(level - 1, child_height, child_radius, p);
		draw_tree_leaf(level, child_height, p);
	glPopMatrix();

	// 侧面的树枝-1
	glPushMatrix();
		glTranslatef(0, height / 3 * 2, 0);
		glRotatef(60, 1, 0, 0);
		draw_tree_recursion(level - 1, child_height, child_radius, p);
		draw_tree_leaf(level, child_height, p);
	glPopMatrix();

	// 侧面的树枝-2
	glPushMatrix();
		glTranslatef(0, height / 3 * 2, 0);
		glRotatef(60, 1, 0, 0);
		glRotatef(120, 0, 1, 0);
		glRotatef(120, 0, 0, 1);
		glRotatef(90, 1, 0, 0);
		draw_tree_recursion(level - 1, child_height, child_radius, p);
		draw_tree_leaf(level, child_height, p);
	glPopMatrix();

	// 侧面的树枝-3
	glPushMatrix();
		glTranslatef(0, height / 3 * 2, 0);
		glRotatef(60, 1, 0, 0);
		glRotatef(240, 0, 1, 0);
		glRotatef(240, 0, 0, 1);
		glRotatef(90, 1, 0, 0);
		draw_tree_recursion(level - 1, child_height, child_radius, p);
		draw_tree_leaf(level, child_height, p);
	glPopMatrix();


}

void draw_tree_main(plant p) {
	if (p.tree_level < 1)
		return;
	glPushMatrix();
		glColor3f(0.8f, 0.7f, 0.5f);
		glTranslatef(p.map_X*4+2, 0, p.map_Z*4+2);
		glRotatef(270, 1, 0, 0);
		GLUquadric *qObj = gluNewQuadric();
		gluCylinder(qObj, p.tree_big_r, p.tree_little_r, p.tree_height, CYLINDER_SLICES, CYLINDER_STACKS);
		glRotatef(90, 1, 0, 0);

		float child_height = p.tree_height / 2;
		float child_radius = p.tree_little_r;

		// 上面的树枝
		glPushMatrix();
			glTranslatef(0, p.tree_height, 0);
			draw_tree_recursion(p.tree_level - 1, child_height, child_radius, p);
		glPopMatrix();

		// 侧面的树枝-1
		glPushMatrix();
			glTranslatef(0, p.tree_height / 3 * 2, 0);
			glRotatef(60, 1, 0, 0);
			draw_tree_recursion(p.tree_level - 1, child_height, child_radius, p);
		glPopMatrix();

		// 侧面的树枝-2
		glPushMatrix();
			glTranslatef(0, p.tree_height / 3 * 2, 0);
			glRotatef(60, 1, 0, 0);
			glRotatef(120, 0, 1, 0);
			glRotatef(120, 0, 0, 1);
			glRotatef(90, 1, 0, 0);
			draw_tree_recursion(p.tree_level - 1, child_height, child_radius, p);
		glPopMatrix();

		// 侧面的树枝-3
		glPushMatrix();
			glTranslatef(0, p.tree_height / 3 * 2, 0);
			glRotatef(60, 1, 0, 0);
			glRotatef(240, 0, 1, 0);
			glRotatef(240, 0, 0, 1);
			glRotatef(90, 1, 0, 0);
			draw_tree_recursion(p.tree_level - 1, child_height, child_radius, p);
		glPopMatrix();


	glPopMatrix();
}






void initPlant() {
	for (int i = 0; i < PLANT_NUM; i++) {
		for (int j = 0; j < PLANT_NUM; j++) {
			plant_data[i*PLANT_NUM + j].plant_type = PLANT_TYPE_NONE;
			plant_data[i*PLANT_NUM + j].map_X = 0;
			plant_data[i*PLANT_NUM + j].map_Z = 0;
			plant_data[i*PLANT_NUM + j].tree_level = 0;
			plant_data[i*PLANT_NUM + j].tree_height = 0.0;
			plant_data[i*PLANT_NUM + j].tree_big_r = 0.0;
			plant_data[i*PLANT_NUM + j].tree_little_r = 0.0;
			plant_data[i*PLANT_NUM + j].tree_leaf_num = 0;
			plant_data[i*PLANT_NUM + j].tree_leaf_size = 0.0;
			plant_data[i*PLANT_NUM + j].tree_leaf_type = 0;
		}
	}
	/*plant_data[12 * PLANT_NUM + 12].plant_type = PLANT_TYPE_TREE;
	plant_data[12 * PLANT_NUM + 12].map_X = 12;
	plant_data[12 * PLANT_NUM + 12].map_Z = 12;
	plant_data[12 * PLANT_NUM + 12].tree_level = 4;
	plant_data[12 * PLANT_NUM + 12].tree_height = 5.0;
	plant_data[12 * PLANT_NUM + 12].tree_big_r = 0.3;
	plant_data[12 * PLANT_NUM + 12].tree_little_r = 0.1;
	plant_data[12 * PLANT_NUM + 12].tree_leaf_num = 5;
	plant_data[12 * PLANT_NUM + 12].tree_leaf_size = 0.3;
	plant_data[12 * PLANT_NUM + 12].tree_leaf_type = 1;

	plant_data[12 * PLANT_NUM + 13].plant_type = PLANT_TYPE_TREE;
	plant_data[12 * PLANT_NUM + 13].map_X = 12;
	plant_data[12 * PLANT_NUM + 13].map_Z = 14;
	plant_data[12 * PLANT_NUM + 13].tree_level = 4;
	plant_data[12 * PLANT_NUM + 13].tree_height = 5.0;
	plant_data[12 * PLANT_NUM + 13].tree_big_r = 0.3;
	plant_data[12 * PLANT_NUM + 13].tree_little_r = 0.1;
	plant_data[12 * PLANT_NUM + 13].tree_leaf_num = 5;
	plant_data[12 * PLANT_NUM + 13].tree_leaf_size = 0.3;
	plant_data[12 * PLANT_NUM + 13].tree_leaf_type = 1;*/

}

void savePlant() {
	plant_stream.open("Data/plantdata", std::ios::out | std::ios::in);
	if (plant_stream.is_open()) {
		fprintf(stdout, "Plant file open success\n");
	}
	else {
		fprintf(stderr, "Plant file open fail\n");
	}
	plant_stream.write((char*)(plant_data), sizeof(plant)* PLANT_NUM * PLANT_NUM);
	fprintf(stdout, "Plant file save success\n");
	plant_stream.close();
}


void readPlant() {
	plant_stream.open("Data/plantdata", std::ios::out | std::ios::binary | std::ios::in);
	if (plant_stream.is_open()) {
		fprintf(stdout, "Plant file open success\n");
	}
	else {
		fprintf(stderr, "Plant file open fail\n");
	}
	plant_stream.read((char*)(plant_data), sizeof(plant)* PLANT_NUM * PLANT_NUM);
	fprintf(stdout, "Plant file save success\n");
	plant_stream.close();
}




void render_tree() {

	for (int i = 0; i < PLANT_NUM; i++) {
		for (int j = 0; j < PLANT_NUM; j++) {
			if (plant_data[i*PLANT_NUM + j].plant_type == PLANT_TYPE_TREE) {
				draw_tree_main(plant_data[i*PLANT_NUM + j]);
			}
			else if (plant_data[i*PLANT_NUM + j].plant_type == PLANT_TYPE_FLOWER) {
				;
			}
		}
	}

}