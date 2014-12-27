#include "screenui.h"


void render_screenui()
{
	


	glPushMatrix();
	glTranslatef(x + UI_DISNTANCE*lx, y - UI_DISNTANCE * ly, z + UI_DISNTANCE * lz);
	glRotatef(-angle_plane / MY_PI * 180, 0, 1.0f, 0);
	glRotatef(-angle_updown / MY_PI * 180, 1.0f, 0, 0);

	
	disable_color_material();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[14]);
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