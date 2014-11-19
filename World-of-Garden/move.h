#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>


extern float angle_plane;
extern float speed_turn_plane;
extern float speed_move;
extern float ratio;
extern float x, y, z;
extern float lx, ly, lz;
extern GLint snowman_display_list;


void turn_left();
void turn_right();
void walk_ahead();
void walk_back();
void walk_left();
void walk_right();

void orient_me(float ang);
void move_ab(int i);
void move_lr(int i);

void initKeyBord();