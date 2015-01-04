#include "screenui.h"


void render_screenui()
{
	glPushMatrix();
	glTranslatef(x + UI_DISNTANCE*lx, y - UI_DISNTANCE * ly, z + UI_DISNTANCE * lz);
	glRotatef(-angle_plane / MY_PI * 180, 0, 1.0f, 0);
	glRotatef(-angle_updown / MY_PI * 180, 1.0f, 0, 0);

	
	disable_color_material();
	glEnable(GL_TEXTURE_2D);
	if (snow_active_speed == 0)
		glBindTexture(GL_TEXTURE_2D, texture[12]);
	else if (snow_active_speed == 2)
		glBindTexture(GL_TEXTURE_2D, texture[13]);
	else if (snow_active_speed == 4)
		glBindTexture(GL_TEXTURE_2D, texture[14]);
	else if (snow_active_speed == 6)
		glBindTexture(GL_TEXTURE_2D, texture[15]);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(UI_X0, UI_Y0, 0);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(UI_X1, UI_Y0, 0);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(UI_X1, UI_Y1, 0);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(UI_X0, UI_Y1, 0);
	glEnd();
	
	glDisable(GL_TEXTURE_2D);
	enable_color_material();
	
	glPopMatrix();

}

#define WINDOW_LENGTH	1024
#define WINDOW_WIDTH	690
void click_screenui(int x, int y)
{
	if (x >= WINDOW_LENGTH - 195 && x <= WINDOW_LENGTH - 160 && y >= 564 && y <= 604)
		ui_click_up();
	else if (x >= WINDOW_LENGTH - 195 && x <= WINDOW_LENGTH - 160 && y >= 644 && y <= 682)
		ui_click_down();
	else if (x >= WINDOW_LENGTH - 232 && x <= WINDOW_LENGTH - 195 && y >= 605 && y <= 642)
		ui_click_left();
	else if (x >= WINDOW_LENGTH - 153 && x <= WINDOW_LENGTH - 118 && y >= 606 && y <= 641)
		ui_click_right();
	else if (x >= WINDOW_LENGTH - 65 && x <= WINDOW_LENGTH - 27 && y >= 574 && y <= 614)
		ui_click_plus();
	else if (x >= WINDOW_LENGTH - 65 && x <= WINDOW_LENGTH - 27 && y >= 636 && y <= 675)
		ui_click_decrease();
}

void ui_click_up() {
	printf("click up\n");
	if (wind_z_accelerate > -0.5)
		wind_z_accelerate -= 0.05;
}

void ui_click_down() {
	printf("click down\n");
	if (wind_z_accelerate < 0.5)
		wind_z_accelerate += 0.05;
}

void ui_click_left() {
	printf("click left\n");
	if (wind_x_accelerate > -0.5)
		wind_x_accelerate -= 0.05;
}

void ui_click_right() {
	printf("click right\n");
	if (wind_x_accelerate < 0.5)
		wind_x_accelerate += 0.05;
}

void ui_click_plus() {
	printf("click plust\n");
	if (snow_active_speed < 6)
		snow_active_speed+=2;
}

void ui_click_decrease() {
	printf("click decrease\n");
	if (snow_active_speed > 0)
		snow_active_speed-=2;
}