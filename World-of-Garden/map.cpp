#include "map.h"


std::fstream terrain_stream;
std::fstream map_texture_stream;
void* terrain = malloc(MAP_SIZE * MAP_SIZE);
GLuint texture[TEXTURE_NUM];

// 雪斑点对象数组
Terrain_snow* snow_spot = new Terrain_snow[MAP_SIZE * MAP_SIZE / STEP_SIZE / STEP_SIZE];

Terrain_snow::Terrain_snow()
{
	spot_count = 0;
}

Terrain_snow::~Terrain_snow()
{}

void Terrain_snow::add_spot(float pos_x, float pos_z)
{	
	spot_count++;
	if (spot_count > MAX_SPOT_PER_TERRAIN && ((spot_count-MAX_SPOT_PER_TERRAIN)%SPOT_PER_HEIGHT==0)) {
		int terrain_spot_x = ((int)pos_x / STEP_SIZE) * STEP_SIZE;
		int terrain_spot_z = ((int)pos_z / STEP_SIZE) * STEP_SIZE;
		for (int i = 0; i <= STEP_SIZE; i++) {
			for (int j = 0; j <= STEP_SIZE; j++) {
				int temp_height = get_terran_height(terrain_spot_x + i, terrain_spot_z + j);
				((unsigned char*)terrain)[terrain_spot_x + i + (terrain_spot_z + j)*MAP_SIZE] = temp_height + SNOW_ADD_HEIGHT;
			}
		}

	}
	
}

/*
bool Terrain_snow::is_accumulation()
{
	if (spot_count < MAX_SPOT_PER_TERRAIN)
		return false;
	return true;
}
*/










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

	disable_color_material();
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
			enable_color_material();
			glBegin(GL_QUADS);
			glColor3f(0.3f, 0.6f, 0.9f);
			

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

			disable_color_material();
			continue;
		}

		/*
		// 混合渲染测试
		else if (X == 88 && Y == 80) {

			glEnd();
			glDisable(GL_TEXTURE_2D);

			
			glActiveTextureARB(GL_TEXTURE0_ARB);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texture[0]);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_EXT);
			glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_RGB_EXT, GL_REPLACE);

			glActiveTextureARB(GL_TEXTURE1_ARB);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texture[1]);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_EXT);
			glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_RGB_EXT, GL_ADD);
			

			

			glBegin(GL_QUADS);

			x = X;
			y = get_terran_height(X, Y);
			z = Y;
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0, 0);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0, 0);
			glVertex3f(x, y / HEIGHT_RATIO, z);
			x = X;
			y = get_terran_height(X, Y + STEP_SIZE);
			z = Y + STEP_SIZE;
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1, 0);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 1, 0);
			glVertex3f(x, y / HEIGHT_RATIO, z);
			x = X + STEP_SIZE;
			y = get_terran_height(X + STEP_SIZE, Y + STEP_SIZE);
			z = Y + STEP_SIZE;
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1, 1);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 1, 1);
			glVertex3f(x, y / HEIGHT_RATIO, z);
			x = X + STEP_SIZE;
			y = get_terran_height(X + STEP_SIZE, Y);
			z = Y;
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0, 1);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0, 1);
			glVertex3f(x, y / HEIGHT_RATIO, z);


			glEnd();


			glActiveTextureARB(GL_TEXTURE1_ARB);
			glDisable(GL_TEXTURE_2D);
			glActiveTextureARB(GL_TEXTURE0_ARB);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texture[0]);
			
			//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_EXT);
			//glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_RGB_EXT, GL_ADD);

			glBegin(GL_QUADS);

			continue;
		}
		*/

		
		// 草地和雪地渲染
		Terrain_snow this_terrain_snow = snow_spot[X / STEP_SIZE + Y / STEP_SIZE * MAP_SIZE / STEP_SIZE];
		int use_texture = this_terrain_snow.spot_count;
		if (use_texture > MAX_SPOT_PER_TERRAIN) {
			use_texture = MAX_SPOT_PER_TERRAIN;
		}
		glDisable(GL_TEXTURE_2D);
		glEnd();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[use_texture]);
		glBegin(GL_QUADS);
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
	enable_color_material();
}


void render_wall() {
	// 画墙
	disable_color_material();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[11]);
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
	enable_color_material();
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
	std::string img_name[TEXTURE_NUM];
	img_name[0] = "Data/snowgrass_0.bmp";
	img_name[1] = "Data/snowgrass_1.bmp";
	img_name[2] = "Data/snowgrass_2.bmp";
	img_name[3] = "Data/snowgrass_3.bmp";
	img_name[4] = "Data/snowgrass_4.bmp";
	img_name[5] = "Data/snowgrass_5.bmp";
	img_name[6] = "Data/snowgrass_6.bmp";
	img_name[7] = "Data/snowgrass_7.bmp";
	img_name[8] = "Data/snowgrass_8.bmp";
	img_name[9] = "Data/snowgrass_9.bmp";
	img_name[10] = "Data/snowgrass_10.bmp";
	img_name[11] = "Data/wall.bmp";


	for (int i = 0; i < TEXTURE_NUM; i++) {
		char* temp_path = new char[img_name[i].size() + 1];
		memcpy(temp_path, img_name[i].c_str(), img_name[i].size() + 1);
		if (TextureImage[i] = LoadBMP(temp_path)) {
			Status = TRUE;
			glGenTextures(1, &texture[i]);
			glBindTexture(GL_TEXTURE_2D, texture[i]);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, TextureImage[i]->sizeX, TextureImage[i]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[i]->data);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
		if (TextureImage[i]) {
			if (TextureImage[i]->data) {
				free(TextureImage[i]->data);
			}
			free(TextureImage[i]);
		}
	}

	return Status;
}


void initMapTexture() {
	LoadGLTextures();

}


void initTerran() {
	load_terran();
}


