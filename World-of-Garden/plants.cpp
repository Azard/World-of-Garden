#include "plants.h"




void draw_tree_leaf(int level, float height, tree_leaf leaf_data) {
	if (level <= 1)
		return;
	int num = leaf_data.num;
	float size = leaf_data.size;

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




void draw_tree_recursion(int level, float height, float radius, tree_leaf leaf_data) {
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
		draw_tree_recursion(level - 1, child_height, child_radius, leaf_data);
		draw_tree_leaf(level, child_height, leaf_data);
	glPopMatrix();

	// 侧面的树枝-1
	glPushMatrix();
		glTranslatef(0, height / 3 * 2, 0);
		glRotatef(60, 1, 0, 0);
		draw_tree_recursion(level - 1, child_height, child_radius, leaf_data);
		draw_tree_leaf(level, child_height, leaf_data);
	glPopMatrix();

	// 侧面的树枝-2
	glPushMatrix();
		glTranslatef(0, height / 3 * 2, 0);
		glRotatef(60, 1, 0, 0);
		glRotatef(120, 0, 1, 0);
		glRotatef(120, 0, 0, 1);
		glRotatef(90, 1, 0, 0);
		draw_tree_recursion(level - 1, child_height, child_radius, leaf_data);
		draw_tree_leaf(level, child_height, leaf_data);
	glPopMatrix();

	// 侧面的树枝-3
	glPushMatrix();
		glTranslatef(0, height / 3 * 2, 0);
		glRotatef(60, 1, 0, 0);
		glRotatef(240, 0, 1, 0);
		glRotatef(240, 0, 0, 1);
		glRotatef(90, 1, 0, 0);
		draw_tree_recursion(level - 1, child_height, child_radius, leaf_data);
		draw_tree_leaf(level, child_height, leaf_data);
	glPopMatrix();


}


void draw_tree_main(int x, int y, int level, float height, float bottom_radius, float top_radius, tree_leaf leaf_data) {
	if (level < 1)
		return;
	glPushMatrix();
		glColor3f(0.8f, 0.7f, 0.5f);
		glTranslatef(x, 0, y);
		glRotatef(270, 1, 0, 0);
		GLUquadric *qObj = gluNewQuadric();
		gluCylinder(qObj, bottom_radius, top_radius, height, CYLINDER_SLICES, CYLINDER_STACKS);
		glRotatef(90, 1, 0, 0);

		float child_height = height / 2;
		float child_radius = top_radius;

		// 上面的树枝
		glPushMatrix();
			glTranslatef(0, height, 0);
			draw_tree_recursion(level - 1, child_height, child_radius, leaf_data);
		glPopMatrix();

		// 侧面的树枝-1
		glPushMatrix();
			glTranslatef(0, height / 3 * 2, 0);
			glRotatef(60, 1, 0, 0);
			draw_tree_recursion(level - 1, child_height, child_radius, leaf_data);
		glPopMatrix();

		// 侧面的树枝-2
		glPushMatrix();
			glTranslatef(0, height / 3 * 2, 0);
			glRotatef(60, 1, 0, 0);
			glRotatef(120, 0, 1, 0);
			glRotatef(120, 0, 0, 1);
			glRotatef(90, 1, 0, 0);
			draw_tree_recursion(level - 1, child_height, child_radius, leaf_data);
		glPopMatrix();

		// 侧面的树枝-3
		glPushMatrix();
			glTranslatef(0, height / 3 * 2, 0);
			glRotatef(60, 1, 0, 0);
			glRotatef(240, 0, 1, 0);
			glRotatef(240, 0, 0, 1);
			glRotatef(90, 1, 0, 0);
			draw_tree_recursion(level - 1, child_height, child_radius, leaf_data);
		glPopMatrix();


	glPopMatrix();
}











void render_tree() {
	//setData();
	//drawTree(3);
	tree_leaf leaf_data1;
	leaf_data1.num = 5;
	leaf_data1.size = 0.3;
	leaf_data1.type = 1;
	draw_tree_main(50, 50, 3, 5.0, 0.3, 0.1, leaf_data1);
}