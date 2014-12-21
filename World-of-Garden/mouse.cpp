#include "mouse.h"

float mouse_turn_view_speed_lr = 0.005f;
float mouse_turn_view_speed_ud = 0.005f;
bool click_left =false;
bool click_right = false;
int mouse_x_pos = 0;
int mouse_y_pos = 0;


void mouse_turn_view(int x, int y) {
	angle_plane += x * mouse_turn_view_speed_lr;
	angle_updown += y * mouse_turn_view_speed_ud;
	flush_view(angle_plane, angle_updown);
}


void initMouseClick(int button, int state, int x, int y) {
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
			click_left = true;
		else if (state == GLUT_UP)
			click_left = false;
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
			click_right = true;
		else if (state == GLUT_UP)
			click_right = false;
		break;
	case GLUT_MIDDLE_BUTTON:
	default:
		break;
	}

	if (state == GLUT_DOWN) {
		mouse_x_pos = x;
		mouse_y_pos = y;
	}
}

void initMouseClickMove(int x, int y) {
	if (click_right) {
		mouse_turn_view(x - mouse_x_pos, y - mouse_y_pos);
		mouse_x_pos = x;
		mouse_y_pos = y;
	}
}

void initMouseMove(int x, int y) {
	mouse_x_pos = x;
	mouse_y_pos = y;
}


void initMouse() {
	glutMouseFunc(initMouseClick);
	glutMotionFunc(initMouseClickMove);
	//glutPassiveMotionFunc(initMouseMove);
}