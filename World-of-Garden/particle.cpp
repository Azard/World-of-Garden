#include "particle.h"


// 重力相关系数
float gravity_accelerate = 0.1;
float particle_y_reverse = 1.0;
// 风相关系数
float wind_x_accelerate = 0.0;
float wind_z_accelerate = 0.0;
float particle_x_reverse = 1.0;
float particle_z_reverse = 1.0;

// 雪粒子数组
#define MAX_PARTICLE_NUM 4000
Particle* snow = new Particle[MAX_PARTICLE_NUM];
int snow_active_count = 0;
int snow_active_speed = 2;
#define SNOW_ACTIVE_Y 20.0


Particle::Particle()
{
	active = false;
	pos_x = pos_y = pos_z = 0.0;
	speed_x = speed_y = speed_z = 0.0;
	accelerate_x = accelerate_y = accelerate_z = 0.0;
	color_r = color_g = color_b = 0.0;
	radius = 0.0;
}

Particle::~Particle()
{}

void Particle::init()
{
	active = false;
	pos_x = pos_y = pos_z = 0.0;
	speed_x = speed_y = speed_z = 0.0;
	accelerate_x = accelerate_y = accelerate_z = 0.0;
	color_r = color_g = color_b = 0.0;
	radius = 0.0;
}

void Particle::activate()
{
	pos_x = rand() * MAP_SIZE / RAND_MAX;
	pos_z = rand() * MAP_SIZE / RAND_MAX;
	
	//pos_x = (rand() * MAP_SIZE / RAND_MAX) % 4 + 88;
	//pos_z = (rand() * MAP_SIZE / RAND_MAX) % 4 + 80;

	pos_y = SNOW_ACTIVE_Y;
	speed_x = 0.0;
	speed_y = 0.0;
	speed_z = 0.0;
	accelerate_x = wind_x_accelerate;
	accelerate_y = gravity_accelerate;
	accelerate_z = wind_z_accelerate;
	color_r = color_g = color_b = 1.0f;
	radius = rand() * 10.0 / RAND_MAX + 10.0;
	active = true;
}

void Particle::update()
{
	// 速度变化
	speed_x += accelerate_x - speed_x * particle_x_reverse;
	speed_z += accelerate_z - speed_z * particle_z_reverse;
	speed_y += accelerate_y - speed_y * particle_y_reverse;
	// 位置变化
	pos_x += speed_x;
	pos_z += speed_z;
	pos_y -= speed_y;

	// 出界并且低于地面
	if ((pos_y <= 0) && (pos_x <= 0 || pos_x >= MAP_SIZE || pos_z <= 0 || pos_z >= MAP_SIZE)) {
		active = false;
		snow_active_count--;
	}
	// 地面碰撞判定，crash_terrain函数内实现了active和count的更新
	if (active == true) {
		crash_terrain();
	}
	

}

void Particle::render()
{
	glPushMatrix();
		glTranslatef(pos_x, pos_y, pos_z);
		glutSolidSphere(0.1f, 6, 6);
	glPopMatrix();
}

void Particle::crash_terrain() {

	// 线性插值
	float pos_height = (float)get_terran_height(pos_x, pos_z) / HEIGHT_RATIO;
	// 双线性插值
	int base_x = ((int)pos_x / STEP_SIZE) * STEP_SIZE;
	int base_z = ((int)pos_z / STEP_SIZE) * STEP_SIZE;
	float height_0 = (float)get_terran_height(base_x, base_z) / HEIGHT_RATIO;
	float height_1 = (float)get_terran_height(base_x + STEP_SIZE, base_z) / HEIGHT_RATIO;
	float height_2 = (float)get_terran_height(base_x + STEP_SIZE, base_z + STEP_SIZE) / HEIGHT_RATIO;
	float height_3 = (float)get_terran_height(base_x, base_z + STEP_SIZE) / HEIGHT_RATIO;
	// 减少判断次数
	if (pos_y > height_0 && pos_y > height_1 && pos_y > height_2 && pos_y > height_3)
		return;
	float height_real = (height_0*((float)base_x + STEP_SIZE - pos_x)*((float)base_z + STEP_SIZE - pos_z)
		+ height_1*(pos_x - (float)base_x)*((float)base_z + STEP_SIZE - pos_z)
		+ height_2*(pos_x - (float)base_x)*(pos_z - (float)base_z)
		+ height_3*((float)base_x + STEP_SIZE - pos_x)*(pos_z - (float)base_z))
		/ (STEP_SIZE * STEP_SIZE);
	if (pos_y < height_real) {
		active = false;
		snow_active_count--;
		int terrain_spot_x = (int)pos_x / STEP_SIZE;
		int terrain_spot_z = (int)pos_z / STEP_SIZE;
		snow_spot[terrain_spot_x + terrain_spot_z * MAP_SIZE / STEP_SIZE].add_spot(pos_x, pos_z);
		// 加入雪到map的spot里
		/*
		int terrain_spot_x = (int)pos_x / STEP_SIZE;
		int terrain_spot_z = (int)pos_z / STEP_SIZE;
		snow_spot[terrain_spot_x + terrain_spot_z * MAP_SIZE / STEP_SIZE].add_spot(pos_x, pos_z);
		*/
	}
}



// 更新雪的数据
void updateSnow()
{
	int new_active = 0;
	for (int i = 0; i < MAX_PARTICLE_NUM; i++) {
		// 新的粒子生成判定
		if (snow[i].active == false) {
			if (new_active < snow_active_speed) {
				snow[i].activate();
				new_active++;
				snow_active_count++;
			}
			continue;
		}
		// 数据更新
		snow[i].update();
	}
}

// 渲染雪
void render_snow()
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glDisable(GL_LIGHTING);
	for (int i = 0; i < MAX_PARTICLE_NUM; i++) {
		if (snow[i].active == false)
			continue;
		snow[i].render();
	}
	glEnable(GL_LIGHTING);
}





