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
	else if (snow_active_speed == 1)
		glBindTexture(GL_TEXTURE_2D, texture[13]);
	else if (snow_active_speed == 2)
		glBindTexture(GL_TEXTURE_2D, texture[14]);
	else if (snow_active_speed == 3)
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
#define WINDOW_WIDTH	768
void click_screenui(int x, int y)
{
	if (x >= WINDOW_LENGTH - 214 && x <= WINDOW_LENGTH - 179 && y >= 630 && y <= 665)
		ui_click_up();
	else if (x >= WINDOW_LENGTH - 214 && x <= WINDOW_LENGTH - 179 && y >= 717 && y <= 756)
		ui_click_down();
	else if (x >= WINDOW_LENGTH - 259 && x <= WINDOW_LENGTH - 219 && y >= 674 && y <= 714)
		ui_click_left();
	else if (x >= WINDOW_LENGTH - 171 && x <= WINDOW_LENGTH - 131 && y >= 674 && y <= 714)
		ui_click_right();
	else if (x >= WINDOW_LENGTH - 74 && x <= WINDOW_LENGTH - 32 && y >= 644 && y <= 682)
		ui_click_plus();
	else if (x >= WINDOW_LENGTH - 74 && x <= WINDOW_LENGTH - 32 && y >= 710 && y <= 749)
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
	if (snow_active_speed < 3)
		snow_active_speed++;
}

void ui_click_decrease() {
	printf("click decrease\n");
	if (snow_active_speed > 0)
		snow_active_speed--;
}