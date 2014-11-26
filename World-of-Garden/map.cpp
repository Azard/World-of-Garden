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
	terrain_stream.close();
}

int get_terran_height(int x, int y) {
	x = x % MAP_SIZE;
	y = y % MAP_SIZE;
	return ((unsigned char*)terrain)[x + (y * MAP_SIZE)];
}

void set_terrain_height(int height_plus) {
	int start_x = select_x / STEP_SIZE * STEP_SIZE;
	int start_z = select_z / STEP_SIZE * STEP_SIZE;
	int save_height[(STEP_SIZE +1)* (STEP_SIZE+1)];
	for (int i = 0; i <= STEP_SIZE; i++) {
		for (int j = 0; j <= STEP_SIZE; j++) {
			save_height[i*(STEP_SIZE+1) + j] = get_terran_height(start_x + i, start_z + j);
			save_height[i*(STEP_SIZE+1) + j] += height_plus;
			if (save_height[i*(STEP_SIZE+1) + j] < 0)
				save_height[i*(STEP_SIZE+1) + j] = 0;
			((unsigned char*)terrain)[start_x+i + (start_z+j)*MAP_SIZE] = save_height[i*(STEP_SIZE+1)+j];
		}
	}
	std::ostringstream s1;
	int s_height = get_terran_height(select_x, select_z);
	s1 << s_height;
	std::string s2 = s1.str();
	UI->terrain_height_text->set_text(("terrain height: " + s2).c_str());	
}

void terrain_save() {
	terrain_stream.open("Data/Terrain.raw", std::ios::out | std::ios::binary | std::ios::in);
	if (terrain_stream.is_open()) {
		fprintf(stdout, "Terrain file open success\n");
	}
	else {
		fprintf(stderr, "Terrain file open fail\n");
	}
	terrain_stream.write((char*)terrain, MAP_SIZE * MAP_SIZE);
	fprintf(stdout, "Terrain file save success\n");
	terrain_stream.close();
}

void render_height_map()
{
	int X = 0, Y = 0;
	float x, y, z;

	// 画地
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
	for (X = 0; X < (MAP_SIZE); X += STEP_SIZE)
	for (Y = 0; Y < (MAP_SIZE); Y += STEP_SIZE)
	{
		// 判断是否为选定区域
		if (select_x <= X + STEP_SIZE && select_x > X && select_z <= Y + STEP_SIZE && select_z > Y) {
			glEnd();
			glDisable(GL_TEXTURE_2D);
			glBegin(GL_QUADS);

			x = X;
			y = get_terran_height(X, Y);
			z = Y;
			glVertex3f(x, y / HEIGHT_RATIO, z);
			x = X;
			y = get_terran_height(X, Y + STEP_SIZE);
			z = Y + STEP_SIZE;
			glVertex3f(x, y / HEIGHT_RATIO, z);
			x = X + STEP_SIZE;
			y = get_terran_height(X + STEP_SIZE, Y + STEP_SIZE);
			z = Y + STEP_SIZE;
			glVertex3f(x, y / HEIGHT_RATIO, z);
			x = X + STEP_SIZE;
			y = get_terran_height(X + STEP_SIZE, Y);
			z = Y;
			glVertex3f(x, y / HEIGHT_RATIO, z);

			glEnd();
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texture[0]);
			glBegin(GL_QUADS);
			continue;
		}
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
	// 画墙
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


