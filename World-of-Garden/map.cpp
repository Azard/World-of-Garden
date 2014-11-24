#include "map.h"


std::fstream terrain_stream;
std::fstream map_texture_stream;
void* terrain = malloc(MAP_SIZE * MAP_SIZE);
GLuint texture[TEXTURE_NUM];


void load_terran() {
	terrain_stream.open("Data/Terrain.raw", std::ios::out | std::ios::binary | std::ios::in);
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
	return ((unsigned char*)terrain)[x + (y * MAP_SIZE)];
}

void render_height_map()
{
	int X = 0, Y = 0;
	float x, y, z;

	// »­µØ
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
	for (X = 0; X < (MAP_SIZE); X += STEP_SIZE)
	for (Y = 0; Y < (MAP_SIZE); Y += STEP_SIZE)
	{
		x = X;
		y = get_terran_height(X, Y);
		z = Y;
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(x, y / HEIGHT_RATIO, z);

		x = X;
		y = get_terran_height(X, Y + STEP_SIZE);
		z = Y + STEP_SIZE;
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(x, y / HEIGHT_RATIO, z);
		x = X + STEP_SIZE;
		y = get_terran_height(X + STEP_SIZE, Y + STEP_SIZE);
		z = Y + STEP_SIZE;
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(x, y / HEIGHT_RATIO, z);

		x = X + STEP_SIZE;
		y = get_terran_height(X + STEP_SIZE, Y);
		z = Y;
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(x, y / HEIGHT_RATIO, z);
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
}


void render_wall() {
	// »­Ç½
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	{
		for (int i = 0; i <= 120; i += 8) {
			glTexCoord2f(0.0f, 0.0f); glVertex3f(i, 0, 0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(i + 8, 0, 0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(i + 8, 8, 0);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(i, 8, 0);
		}
		for (int i = 0; i <= 120; i += 8) {
			glTexCoord2f(0.0f, 0.0f); glVertex3f(128, 0, i);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(128, 0, i + 8);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(128, 8, i + 8);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(128, 8, i);
		}
		for (int i = 0; i <= 120; i += 8) {
			glTexCoord2f(0.0f, 0.0f); glVertex3f(i + 8, 0, 128);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(i, 0, 128);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(i, 8, 128);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(i + 8, 8, 128);
		}
		for (int i = 0; i <= 120; i += 8) {
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, i + 8);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0, i);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(0, 8, i);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(0, 8, i + 8);
		}
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void render_sky() {
	glColor3f(0.3f, 0.6f, 0.9f);
	glPushMatrix();
	glTranslatef(64.0f, 0.0f, 64.0f);
	glutSolidSphere(100.0f, 10, 10);
	glPopMatrix();
}


AUX_RGBImageRec* LoadBMP(char *Filename)
{
	FILE *File = NULL;
	if (!Filename) {
		return NULL;
	}
	File = fopen(Filename, "r");
	if (File) {
		fclose(File);			
		return auxDIBImageLoad(Filename);
	}
	return NULL;
}

int LoadGLTextures()
{
	int Status = FALSE;
	AUX_RGBImageRec* TextureImage[TEXTURE_NUM];
	memset(TextureImage, 0, sizeof(void *)* 1);

	if (TextureImage[0] = LoadBMP("Data/grass2.bmp")) {
		Status = TRUE;
		glGenTextures(1, &texture[0]);
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	if (TextureImage[0]) {
		if (TextureImage[0]->data) {
			free(TextureImage[0]->data);	
		}
		free(TextureImage[0]);
	}


	if (TextureImage[1] = LoadBMP("Data/wall.bmp")) {
		Status = TRUE;
		glGenTextures(1, &texture[1]);
		glBindTexture(GL_TEXTURE_2D, texture[1]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[1]->sizeX, TextureImage[1]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[1]->data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	if (TextureImage[1]) {
		if (TextureImage[1]->data) {
			free(TextureImage[1]->data);
		}
		free(TextureImage[1]);
	}


	return Status;
}


void initMapTexture() {
	LoadGLTextures();
}


void initTerran() {
	load_terran();
}


