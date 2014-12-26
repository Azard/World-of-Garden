#include "glhead.h"

void disable_color_material() {
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glColorMaterial(GL_FRONT_AND_BACK, GL_SPECULAR);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDisable(GL_COLOR_MATERIAL);
}


void enable_color_material() {
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}