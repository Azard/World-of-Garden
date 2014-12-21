#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>


extern float angle_plane;
extern float angle_updown;
extern float ratio;
extern float x, y, z;
extern float lx, ly, lz;
void flush_view(float ang_p, float ang_u);


extern bool click_left;
extern bool click_right;
extern int mouse_x_pos;
extern int mouse_y_pos;


void initMouseClick(int button, int state, int x, int y);
void initMouseClickMove(int x, int y);
void initMouseMove(int x, int y);
void initMouse();