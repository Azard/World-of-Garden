#include "keyboard.h"

float angle_plane = 0.0;
float angle_updown = 0.0;
float speed_turn_plane = 0.03f;
float speed_move = 0.3f;
float ratio;
float x = 0.0f, y = 1.75f, z = 5.0f;
float lx = 0.0f, ly = 0.0f, lz = -1.0f;
int select_x = -1;
int select_z = -1;


void flush_view(float ang_p, float ang_u) {
	lx = sin(ang_p) * cos(ang_u);
	ly = sin(ang_u);
	lz = -cos(ang_p) * cos(ang_u);
	if (y < 3)
		y = 3;
	glLoadIdentity();
	gluLookAt(x, y, z,
		x + lx, y - ly, z + lz,
		0.0f, 1.0f, 0.0f);
	fprintf(stdout, "pos x:%f, z:%f\n", x, z);
}

void move_ab(float i) {
	x = x + i*(lx)*speed_move;
	z = z + i*(lz)*speed_move;
	flush_view(angle_plane, angle_updown);
}

void move_ud(float i) {
	y = y + i*speed_move;
	flush_view(angle_plane, angle_updown);
}

void move_lr(float i) {
	x = x - i*(lz)*speed_move;
	z = z + i*(lx)*speed_move;
	flush_view(angle_plane, angle_updown);
}

void turn_left() {
	if (click_right) {
		walk_left();
		return;
	}
	angle_plane -= speed_turn_plane;
	flush_view(angle_plane, angle_updown);
}

void turn_right() {
	if (click_right) {
		walk_right();
		return;
	}
	angle_plane += speed_turn_plane;
	flush_view(angle_plane, angle_updown);
}

void walk_ahead() {
	move_ab(abs(cos(angle_updown)));
	move_ud(-sin(angle_updown));
}

void walk_back() {
	move_ab(-abs(cos(angle_updown)));
	move_ud(sin(angle_updown));
}

void walk_left() {
	move_lr(-1);
}

void walk_right() {
	move_lr(1);
}

void select_this_land()
{
	fprintf(stdout, "select pos, x:%f, z:%f, lx:%f, lz:%f\n", x, z, lx, lz);
	select_x = x + lx;
	select_z = z + lz;
	if (lx < 0)
		select_x--;
	else
		select_x++;
	if (lz < 0)
		select_z--;
	else
		select_z++;

	std::ostringstream s1, s2;
	s1 << select_x;
	std::string s3 = s1.str();
	UI->terrain_x->set_text(("terrain x: " + s3).c_str());
	s2 << select_z;
	s3 = s2.str();
	UI->terrain_z->set_text(("terrain z: " + s3).c_str());

	fprintf(stdout, "select, x:%d, z:%d\n", select_x, select_z);
}


void initNormalKeys(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		exit(0);
	case 'a':
		turn_left();
		break;
	case 'd':
		turn_right();
		break;
	case 'w':
		walk_ahead();
		break;
	case 's':
		walk_back();
		break;
	case 'q':
		walk_left();
		break;
	case 'e':
		walk_right();
		break;
	case 'c':
		select_this_land();
		break;
	}
}


void initSpecialKeys(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		turn_left();
		break;
	case GLUT_KEY_RIGHT:
		turn_right();
		break;
	case GLUT_KEY_UP:
		walk_ahead();
		break;
	case GLUT_KEY_DOWN:
		walk_back();
		break;
	}
}


void initKeyBord() {
	glutKeyboardFunc(initNormalKeys);
	glutSpecialFunc(initSpecialKeys);
}


