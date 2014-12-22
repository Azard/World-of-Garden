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
#define MAX_PARTICLE_NUM 1000
particle* snow = new particle[MAX_PARTICLE_NUM];
int snow_active_count = 0;
#define SNOW_ACTIVE_Y 40.0


particle::particle()
{
	active = false;
	pos_x = pos_y = pos_z = 0.0;
	speed_x = speed_y = speed_z = 0.0;
	accelerate_x = accelerate_y = accelerate_z = 0.0;
	color_r = color_g = color_b = 0.0;
	radius = 0.0;
}

particle::~particle()
{}

void particle::init()
{
	active = false;
	pos_x = pos_y = pos_z = 0.0;
	speed_x = speed_y = speed_z = 0.0;
	accelerate_x = accelerate_y = accelerate_z = 0.0;
	color_r = color_g = color_b = 0.0;
	radius = 0.0;
}

void particle::activate()
{
	pos_x = rand() * MAP_SIZE / RAND_MAX;
	pos_z = rand() * MAP_SIZE / RAND_MAX;
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

void particle::update()
{
	// 速度变化
	speed_x += accelerate_x - speed_x * particle_x_reverse;
	speed_z += accelerate_z - speed_z * particle_z_reverse;
	speed_y += accelerate_y - speed_y * particle_y_reverse;
	// 位置变化
	pos_x += speed_x;
	pos_z += speed_z;
	pos_y -= speed_y;

	// 碰撞测试
	// crash
	if (pos_y <= 0) {
		active = false;
		snow_active_count--;
	}
}

void particle::render()
{
	glPushMatrix();
		glTranslatef(pos_x, pos_y, pos_z);
		glutSolidSphere(0.1f, 6, 6);
	glPopMatrix();
}


// 更新雪的数据
void updateSnow()
{
	bool new_active = false;
	for (int i = 0; i < MAX_PARTICLE_NUM; i++) {
		// 新的粒子生成判定
		if (snow[i].active == false) {
			if (new_active == false) {
				snow[i].activate();
				new_active = true;
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





