#include "plants.h"

std::fstream plant_stream;
plant* plant_data = new plant[PLANT_NUM * PLANT_NUM];



void draw_tree_leaf(int level, float height, plant p) {
	if (level <= 1)
		return;
	int num = p.tree_leaf_num;
	float size = p.tree_leaf_size;

	if (p.tree_leaf_type == TREE_LEAF_PINE) {
		glBegin(GL_TRIANGLES);
		{
			glColor3f(0.1f, 0.7f, 0.1f);
			for (int i = 0; i < num; i++) {
				float t = height / num;
				glVertex3f(0, t * i, 0);
				glVertex3f(0, size + t * i, 0);
				glVertex3f(size, size + t * i, 0);
			}
			for (int i = 0; i < num; i++) {
				float t = height / num;
				glVertex3f(0, t * i, 0);
				glVertex3f(0, size + t * i, 0);
				glVertex3f(0, size + t * i, size);
			}
			for (int i = 0; i < num; i++) {
				float t = height / num;
				glVertex3f(0, t * i, 0);
				glVertex3f(0, size + t * i, 0);
				glVertex3f(0, size + t * i, -size);
			}
			for (int i = 0; i < num; i++) {
				float t = height / num;
				glVertex3f(0, t * i, 0);
				glVertex3f(0, size + t * i, 0);
				glVertex3f(-size, size + t * i, 0);
			}
		}
		glEnd();
	}
	else if (p.tree_leaf_type == TREE_LEAF_SAKURA) {
		glColor3f(0.953f, 0.602f, 0.754f);
		glPushMatrix();
		for (int i = 0; i < num; i++) {
			float t = height / num;
			glTranslatef(0, t, 0);
			glutSolidSphere(0.1f, 5, 5);
		}
		glPopMatrix();
	}
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
		glTranslatef(p.map_X * 4 + 2, get_terran_height(p.map_X * 4 + 2, p.map_Z * 4 + 2) / HEIGHT_RATIO, p.map_Z * 4 + 2);
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


void draw_flower_main() {
	// 花杆
	glPushMatrix();
		glTranslatef(92, 0, 92);
		glColor3f(0.3f, 1.0f, 0.3f);
		glRotatef(270, 1, 0, 0);
		GLUquadric *qObj = gluNewQuadric();
		gluCylinder(qObj, 0.02f, 0.02f, 1.9f, 10, 10);
		glRotatef(90, 1, 0, 0);
	glPopMatrix();

	// 花芯
	glPushMatrix();
		glTranslatef(92, 2, 92);
		glColor3f(0.9f, 0.9f, 0.1f);
		glutSolidSphere(0.1f, 10, 10);
	glPopMatrix();

	// 花瓣
	glPushMatrix();
		glColor3f(1.0f, 0.2f, 0.2f);
		glTranslatef(92, 2, 92);
		glRotatef(90, 1.0f, 0, 0);

		/*for (int i = 0; i < 6; i++)
			gluPartialDisk(qObj, 0.0f, 0.5f, 10, 10, 0.0f + 60*i, 30.0f);*/

		glRotatef(30, 0, 1.0f, 0);
		for (int i = 0; i < 6; i++)
			gluPartialDisk(qObj, 0.0f, 0.5f, 10, 10, 0.0f + 60 * i, 360.0f);

		glRotatef(-60, 0, 1.0f, 0);
		for (int i = 0; i < 6; i++)
			gluPartialDisk(qObj, 0.0f, 0.5f, 10, 10, 0.0f + 60 * i, 360.0f);

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

	plant_data[12 * PLANT_NUM + 14].plant_type = PLANT_TYPE_TREE;
	plant_data[12 * PLANT_NUM + 14].map_X = 12;
	plant_data[12 * PLANT_NUM + 14].map_Z = 14;
	plant_data[12 * PLANT_NUM + 14].tree_level = 4;
	plant_data[12 * PLANT_NUM + 14].tree_height = 5.0;
	plant_data[12 * PLANT_NUM + 14].tree_big_r = 0.3;
	plant_data[12 * PLANT_NUM + 14].tree_little_r = 0.1;
	plant_data[12 * PLANT_NUM + 14].tree_leaf_num = 5;
	plant_data[12 * PLANT_NUM + 14].tree_leaf_size = 0.3;
	plant_data[12 * PLANT_NUM + 14].tree_leaf_type = 1;*/

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


void select_flush_ui() {

	UI->plant_list_leaf_type->delete_item(1);
	UI->plant_list_leaf_type->delete_item(2);

	std::ostringstream s1;
	s1 << plant_x;
	std::string s2 = s1.str();
	UI->plant_x->set_text(("plant x: " + s2).c_str());
	s1.str("");
	s1 << plant_z;
	s2 = s1.str();
	UI->plant_z->set_text(("plant z: " + s2).c_str());
	s1.str("");

	int get_plant_level = plant_data[plant_x * PLANT_NUM + plant_z].tree_level;
	s1 << get_plant_level;
	s2 = s1.str();
	UI->plant_level->set_text(("plant level: " + s2).c_str());
	s1.str("");

	int get_plant_type = plant_data[plant_x * PLANT_NUM + plant_z].plant_type;
	std::string s_get_plant_type = "";
	if (get_plant_type == PLANT_TYPE_NONE)
		s_get_plant_type = "none";
	else if (get_plant_type == PLANT_TYPE_TREE) {
		s_get_plant_type = "tree";
		UI->plant_list_leaf_type->add_item(TREE_LEAF_PINE, "pine");
		UI->plant_list_leaf_type->add_item(TREE_LEAF_SAKURA, "sakura");
	}
	else if (get_plant_type == PLANT_TYPE_FLOWER)
		s_get_plant_type = "flower";
	UI->plant_type->set_text(("plant type: " + s_get_plant_type).c_str());
	
	float get_plant_height = plant_data[plant_x * PLANT_NUM + plant_z].tree_height;
	std::string s_get_plant_height = "";
	s1 << get_plant_height;
	s_get_plant_height = s1.str();
	UI->plant_height->set_text(("plant height: " + s_get_plant_height).c_str());
	s1.str("");

	float get_plant_big_radius = plant_data[plant_x * PLANT_NUM + plant_z].tree_big_r;
	std::string s_get_plant_big_r = "";
	s1 << get_plant_big_radius;
	s_get_plant_big_r = s1.str();
	UI->plant_big_radius->set_text(("plant big r: " + s_get_plant_big_r).c_str());
	s1.str("");

	float get_plant_small_radius = plant_data[plant_x * PLANT_NUM + plant_z].tree_little_r;
	std::string s_get_small_big_r = "";
	s1 << get_plant_small_radius;
	s_get_small_big_r = s1.str();
	UI->plant_small_radius->set_text(("plant small r: " + s_get_small_big_r).c_str());
	s1.str("");

	int get_plant_leaf_num = plant_data[plant_x * PLANT_NUM + plant_z].tree_leaf_num;
	s1 << get_plant_leaf_num;
	s2 = s1.str();
	UI->plant_leaf_num->set_text(("leaf number: " + s2).c_str());
	s1.str("");

	float get_plant_leaf_size = plant_data[plant_x * PLANT_NUM + plant_z].tree_leaf_size;
	s1 << get_plant_leaf_size;
	s2 = s1.str();
	UI->plant_leaf_size->set_text(("leaf size: " + s2).c_str());
	s1.str("");

	int get_plant_leaf_type = plant_data[plant_x * PLANT_NUM + plant_z].tree_leaf_type;
	s2 = "-";
	if (get_plant_leaf_type == TREE_LEAF_PINE)
		s2 = "pine";
	else if (get_plant_leaf_type == TREE_LEAF_SAKURA)
		s2 = "sakura";
	UI->plant_leaf_type->set_text(("leaf type: " + s2).c_str());
	s1.str("");



}


void ops_delete_plant() {
	plant_data[plant_x * PLANT_NUM + plant_z].plant_type = PLANT_TYPE_NONE;
	select_flush_ui();
}

void ops_create_tree() {
	plant_data[plant_x * PLANT_NUM + plant_z].plant_type = PLANT_TYPE_TREE;
	plant_data[plant_x * PLANT_NUM + plant_z].map_X = plant_x;
	plant_data[plant_x * PLANT_NUM + plant_z].map_Z = plant_z;
	plant_data[plant_x * PLANT_NUM + plant_z].tree_level = 2;
	plant_data[plant_x * PLANT_NUM + plant_z].tree_big_r = 0.3;
	plant_data[plant_x * PLANT_NUM + plant_z].tree_little_r = 0.1;
	plant_data[plant_x * PLANT_NUM + plant_z].tree_height = 5.0;
	plant_data[plant_x * PLANT_NUM + plant_z].tree_leaf_num = 5;
	plant_data[plant_x * PLANT_NUM + plant_z].tree_leaf_size = 0.3;
	plant_data[plant_x * PLANT_NUM + plant_z].tree_leaf_type = 1;
	select_flush_ui();
}


void ops_tree_level(int delta) {
	if (select_x < 0 || select_z < 0)
		return;
	plant_data[plant_x * PLANT_NUM + plant_z].tree_level += delta;
	select_flush_ui();
}

void ops_tree_height(std::string input) {
	float new_height = atof(input.c_str());
	plant_data[plant_x * PLANT_NUM + plant_z].tree_height = new_height;
	select_flush_ui();
}

void ops_tree_big_radius(std::string input) {
	float new_radius = atof(input.c_str());
	plant_data[plant_x * PLANT_NUM + plant_z].tree_big_r = new_radius;
	select_flush_ui();
}

void ops_tree_small_radius(std::string input) {
	float new_radius = atof(input.c_str());
	plant_data[plant_x * PLANT_NUM + plant_z].tree_little_r = new_radius;
	select_flush_ui();
}

void ops_tree_leaf_num(std::string input) {
	float new_num = atof(input.c_str());
	plant_data[plant_x * PLANT_NUM + plant_z].tree_leaf_num = new_num;
	select_flush_ui();
}

void ops_tree_leaf_size(std::string input) {
	float new_size = atof(input.c_str());
	plant_data[plant_x * PLANT_NUM + plant_z].tree_leaf_size = new_size;
	select_flush_ui();
}

void ops_tree_leaf_type(int input) {
	plant_data[plant_x * PLANT_NUM + plant_z].tree_leaf_type = input;
	select_flush_ui();
}


void render_plant() {

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