#include "map.h"


std::fstream terrain_stream;
void* terrain = malloc(MAP_SIZE * MAP_SIZE);


void load_terran() {
	terrain_stream.open("Data/Terrain3.raw", std::ios::out | std::ios::binary | std::ios::in);
	if (terrain_stream.is_open()) {
		fprintf(stdout, "Terrain file open success\n");
	}
	else {
		fprintf(stderr, "Terrain file open fail\n");
	}
	terrain_stream.read((char*)terrain, MAP_SIZE * MAP_SIZE);
}

int get_terran_height(int x, int y) {
	x = x % MAP_SIZE;
	y = y % MAP_SIZE;
	return ((char*)terrain)[x + (y * MAP_SIZE)];
}

void RenderHeightMap()
{
	int X = 0, Y = 0;
	float x, y, z;


	glBegin(GL_QUADS);
	for (X = 0; X < (MAP_SIZE - STEP_SIZE); X += STEP_SIZE)
	for (Y = 0; Y < (MAP_SIZE - STEP_SIZE); Y += STEP_SIZE)
	{

		

		x = X;
		y = get_terran_height(X, Y);
		z = Y;
		glColor3f(0, 0, y / 256.0 + 0.5f);
		glVertex3f(x / 10.0f, y/10 - 20, z / 10.0f);

		x = X;
		y = get_terran_height(X, Y + STEP_SIZE);
		z = Y + STEP_SIZE;
		glColor3f(0, 0, y / 256.0 + 0.5f);
		glVertex3f(x / 10.0f, y/10 - 20, z / 10.0f);

		x = X + STEP_SIZE;
		y = get_terran_height(X + STEP_SIZE, Y + STEP_SIZE);
		z = Y + STEP_SIZE;
		glColor3f(0, 0, y / 256.0 + 0.5f);
		glVertex3f(x / 10.0f, y/10 - 20, z / 10.0f);

		x = X + STEP_SIZE;
		y = get_terran_height(X + STEP_SIZE, Y);
		z = Y;
		glColor3f(0, 0, y / 256.0 + 0.5f);
		glVertex3f(x / 10.0f, y/10 - 20, z / 10.0f);
	}
	glEnd();

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);					// Reset The Color
}


















void initTerran() {
	load_terran();
}