#ifndef SCREENUI
#define SCREENUI
#include "mouse.h"
#include "map.h"
#include "particle.h"
#include "glhead.h"

#define MY_PI 3.1415926
#define UI_DISNTANCE 2

#define UI_X0	0.63
#define UI_X1	1.23
#define UI_Y0	-0.3
#define UI_Y1	-0.9

void render_screenui();
void click_screenui(int x, int y);

void ui_click_left();
void ui_click_right();
void ui_click_up();
void ui_click_down();
void ui_click_plus();
void ui_click_decrease();

#endif