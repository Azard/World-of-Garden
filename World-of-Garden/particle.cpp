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
int snow_active_speed = 4;
#define SNOW_ACTIVE_Y 20.0


Particle::Particle()
{
	active = attach = ever_attach = false;
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
	active = attach = ever_attach = false;
	pos_x = pos_y = pos_z = 0.0;
	speed_x = speed_y = speed_z = 0.0;
	accelerate_x = accelerate_y = accelerate_z = 0.0;
	color_r = color_g = color_b = 0.0;
	radius = 0.0;
}

void Particle::activate()
{
	pos_x = float(rand()) * MAP_SIZE / RAND_MAX + float(rand()) / RAND_MAX;
	pos_z = float(rand()) * MAP_SIZE / RAND_MAX + float(rand()) / RAND_MAX;
	
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
	// 植物碰撞判定
	if (active == true && attach == false) {
		crash_terrain();
		crash_plant();
		if (ever_attach == false)
			crash_flower();
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
	// 双线性插值
	int base_x = ((int)pos_x / STEP_SIZE) * STEP_SIZE;
	int base_z = ((int)pos_z / STEP_SIZE) * STEP_SIZE;
	if (base_x <= 0 || base_x >= 127 || base_z <= 0 || base_z >= 127) {
		active = false;
		snow_active_count--;
	}

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
		// 平摊到旁边
		int index[4];
		bool is_use = false;
		int this_spot_count = snow_spot[terrain_spot_x + terrain_spot_z * MAP_SIZE / STEP_SIZE].spot_count;
		index[0] = terrain_spot_x + terrain_spot_z * MAP_SIZE / STEP_SIZE - 1;
		index[1] = terrain_spot_x + terrain_spot_z * MAP_SIZE / STEP_SIZE + 1;
		index[2] = terrain_spot_x + terrain_spot_z * MAP_SIZE / STEP_SIZE + 32;
		index[3] = terrain_spot_x + terrain_spot_z * MAP_SIZE / STEP_SIZE - 32;
		for (int i = 0; i < 4; i++) {
			if (index[i] < 992 && index[i] > 32 && (snow_spot[index[i]].spot_count + 1 < this_spot_count)) {
				is_use = true;
				if (i == 0)
					pos_x -= 32;
				else if (i == 1)
					pos_x += 32;
				else if (i == 2)
					pos_z += 32;
				else if (i == 3)
					pos_z -= 32;
				snow_spot[index[i]].add_spot(pos_x, pos_z);
				break;
			}
		}
		if (is_use == false)
			snow_spot[terrain_spot_x + terrain_spot_z * MAP_SIZE / STEP_SIZE].add_spot(pos_x, pos_z);
	}
}

void Particle::crash_plant() {
	float origin_pos_x = pos_x - speed_x;
	float origin_pos_z = pos_z - speed_z;
	float origin_pos_y = pos_y + speed_y;
	// 对于每个snow_plant
	for (unsigned i = 0; i < snow_plant.size(); i++) {
		float center_x = snow_plant[i].pos_x * 4 + 2;
		float center_z = snow_plant[i].pos_z * 4 + 2;
		float size = snow_plant[i].size;
		// 减少判断
		if (pos_x < center_x - 10
			|| pos_x > center_x + 10
			|| pos_z < center_z - 10
			|| pos_z > center_z + 10
			|| pos_y > 8.0 * size)
			continue;

		// 碰撞判断，判断有无解
		// 第一层
	LEVEL_1:
		if (origin_pos_y < 6.5*size || pos_y > 8.0*size)
			goto LEVEL_2;
		float form_A = pow((origin_pos_x - pos_x) / (origin_pos_y - pos_y), 2) + pow((origin_pos_z - pos_z) / (origin_pos_y - pos_y), 2) - 1;
		float form_B = 2 * (origin_pos_x - pos_x) * (pos_x * origin_pos_y - origin_pos_x * pos_y) / pow(origin_pos_y - pos_y, 2) - 2 * center_x * (origin_pos_x - pos_x) / (origin_pos_y - pos_y)
			+ 2 * (origin_pos_z - pos_z) * (pos_z * origin_pos_y - origin_pos_z * pos_y) / pow(origin_pos_y - pos_y, 2) - 2 * center_z * (origin_pos_z - pos_z) / (origin_pos_y - pos_y)
			+ 2 * 8 * size;
		float form_C = pow((pos_x * origin_pos_y - origin_pos_x * pos_y) / (origin_pos_y - pos_y), 2) - 2 * center_x * (pos_x * origin_pos_y - origin_pos_x * pos_y) / (origin_pos_y - pos_y) + pow(center_x, 2)
			+ pow((pos_z * origin_pos_y - origin_pos_z * pos_y) / (origin_pos_y - pos_y), 2) - 2 * center_z * (pos_z * origin_pos_y - origin_pos_z * pos_y) / (origin_pos_y - pos_y) + pow(center_z, 2)
			- pow(8 * size, 2);
		float delta = pow(form_B, 2) - 4 * form_A * form_C;
		if (delta < 0)
			goto LEVEL_2;
		bool bool1_level_1 = false;
		bool bool2_level_1 = false;
		float solve1_level_1 = (-form_B + sqrt(delta)) / 2 / form_A;
		float solve2_level_1 = (-form_B - sqrt(delta)) / 2 / form_A;
		if (pos_y <= solve1_level_1 && solve1_level_1 < origin_pos_y
			&& 6.5*size <= solve1_level_1 && solve1_level_1 <= 8.0*size) {
			bool1_level_1 = true;
			this->attach = true;
			snow_plant[i].particle_set_1.push_back((void*)this);
			if (snow_plant[i].particle_set_1.size() >= SNOWPLANT_COLLAPSE_MAX)
				snow_plant[i].collapse_snow_plant_level_1();
		}
		else if (pos_y <= solve2_level_1 && solve2_level_1 < origin_pos_y
			&& 6.5*size <= solve2_level_1 && solve2_level_1 <= 8.0*size) {
			bool2_level_1 = true;
			this->attach = true;
			snow_plant[i].particle_set_1.push_back((void*)this);
			if (snow_plant[i].particle_set_1.size() >= SNOWPLANT_COLLAPSE_MAX)
				snow_plant[i].collapse_snow_plant_level_1();
		}

		// 第二层
	LEVEL_2:
		if (origin_pos_y < 4.8*size || pos_y > 7.0*size)
			goto LEVEL_3;
		form_A = pow((origin_pos_x - pos_x) / (origin_pos_y - pos_y), 2) + pow((origin_pos_z - pos_z) / (origin_pos_y - pos_y), 2) - 1;
		form_B = 2 * (origin_pos_x - pos_x) * (pos_x * origin_pos_y - origin_pos_x * pos_y) / pow(origin_pos_y - pos_y, 2) - 2 * center_x * (origin_pos_x - pos_x) / (origin_pos_y - pos_y)
			+ 2 * (origin_pos_z - pos_z) * (pos_z * origin_pos_y - origin_pos_z * pos_y) / pow(origin_pos_y - pos_y, 2) - 2 * center_z * (origin_pos_z - pos_z) / (origin_pos_y - pos_y)
			+ 2 * 7 * size;
		form_C = pow((pos_x * origin_pos_y - origin_pos_x * pos_y) / (origin_pos_y - pos_y), 2) - 2 * center_x * (pos_x * origin_pos_y - origin_pos_x * pos_y) / (origin_pos_y - pos_y) + pow(center_x, 2)
			+ pow((pos_z * origin_pos_y - origin_pos_z * pos_y) / (origin_pos_y - pos_y), 2) - 2 * center_z * (pos_z * origin_pos_y - origin_pos_z * pos_y) / (origin_pos_y - pos_y) + pow(center_z, 2)
			- pow(7 * size, 2);
		delta = pow(form_B, 2) - 4 * form_A * form_C;
		if (delta < 0)
			goto LEVEL_3;
		bool bool1_level_2 = false;
		bool bool2_level_2 = false;
		float solve1_level_2 = (-form_B + sqrt(delta)) / 2 / form_A;
		float solve2_level_2 = (-form_B - sqrt(delta)) / 2 / form_A;
		if (pos_y <= solve1_level_2 && solve1_level_2 < origin_pos_y
			&& 4.8*size <= solve1_level_2 && solve1_level_2 <= 7.0*size) {
			bool1_level_2 = true;
			this->attach = true;
			snow_plant[i].particle_set_2.push_back((void*)this);
			if (snow_plant[i].particle_set_2.size() >= SNOWPLANT_COLLAPSE_MAX)
				snow_plant[i].collapse_snow_plant_level_2();
		}
		else if (pos_y <= solve2_level_2 && solve2_level_2 < origin_pos_y
			&& 4.8*size <= solve2_level_2 && solve2_level_2 <= 7.0*size) {
			bool2_level_2 = true;
			this->attach = true;
			snow_plant[i].particle_set_2.push_back((void*)this);
			if (snow_plant[i].particle_set_2.size() >= SNOWPLANT_COLLAPSE_MAX)
				snow_plant[i].collapse_snow_plant_level_2();
		}

		// 第三层
	LEVEL_3:
		if (origin_pos_y < 2.5*size || pos_y > 5.5*size)
			goto END;
		form_A = pow((origin_pos_x - pos_x) / (origin_pos_y - pos_y), 2) + pow((origin_pos_z - pos_z) / (origin_pos_y - pos_y), 2) - 1;
		form_B = 2 * (origin_pos_x - pos_x) * (pos_x * origin_pos_y - origin_pos_x * pos_y) / pow(origin_pos_y - pos_y, 2) - 2 * center_x * (origin_pos_x - pos_x) / (origin_pos_y - pos_y)
			+ 2 * (origin_pos_z - pos_z) * (pos_z * origin_pos_y - origin_pos_z * pos_y) / pow(origin_pos_y - pos_y, 2) - 2 * center_z * (origin_pos_z - pos_z) / (origin_pos_y - pos_y)
			+ 2 * 5.5 * size;
		form_C = pow((pos_x * origin_pos_y - origin_pos_x * pos_y) / (origin_pos_y - pos_y), 2) - 2 * center_x * (pos_x * origin_pos_y - origin_pos_x * pos_y) / (origin_pos_y - pos_y) + pow(center_x, 2)
			+ pow((pos_z * origin_pos_y - origin_pos_z * pos_y) / (origin_pos_y - pos_y), 2) - 2 * center_z * (pos_z * origin_pos_y - origin_pos_z * pos_y) / (origin_pos_y - pos_y) + pow(center_z, 2)
			- pow(5.5 * size, 2);
		delta = pow(form_B, 2) - 4 * form_A * form_C;
		if (delta < 0)
			goto END;
		bool bool1_level_3 = false;
		bool bool2_level_3 = false;
		float solve1_level_3 = (-form_B + sqrt(delta)) / 2 / form_A;
		float solve2_level_3 = (-form_B - sqrt(delta)) / 2 / form_A;
		if (pos_y <= solve1_level_3 && solve1_level_3 < origin_pos_y
			&& 2.5*size <= solve1_level_3 && solve1_level_3 <= 5.5*size) {
			bool1_level_3 = true;
			this->attach = true;
			snow_plant[i].particle_set_3.push_back((void*)this);
			if (snow_plant[i].particle_set_3.size() >= SNOWPLANT_COLLAPSE_MAX)
				snow_plant[i].collapse_snow_plant_level_3();
		}
		else if (pos_y <= solve2_level_3 && solve2_level_3 < origin_pos_y
			&& 2.5*size <= solve2_level_3 && solve2_level_3 <= 5.5*size) {
			bool2_level_3 = true;
			this->attach = true;
			snow_plant[i].particle_set_3.push_back((void*)this);
			if (snow_plant[i].particle_set_3.size() >= SNOWPLANT_COLLAPSE_MAX)
				snow_plant[i].collapse_snow_plant_level_3();
		}

	END:
		;
	}
	
}

void Particle::crash_flower()
{
	// 对于每个snow_flower
	for (unsigned i = 0; i < snow_flower.size(); i++) {
		float center_x = snow_flower[i].pos_x * 4 + 2;
		float center_z = snow_flower[i].pos_z * 4 + 2;
		float size = snow_flower[i].size;
		// 减少判断
		if (pos_x < center_x - 2.0*size
			|| pos_x > center_x + 2.0*size
			|| pos_z < center_z - 2.0*size
			|| pos_z > center_z + 2.0*size
			|| pos_y > 3.5 * size)
			continue;
		// 碰撞判断
		float dis = sqrt(pow(pos_x - center_x, 2) + pow(pos_z - center_z, 2));
		if (dis < 1.0*size) {
			pos_y = 3.0*size + dis*0.3;
			this->attach = true;
			this->ever_attach = true;
			snow_flower[i].particle_set_1.push_back((void*)this);
			if (snow_flower[i].particle_set_1.size() >= SNOWFLOWER_COLLAPSE_MAX)
				snow_flower[i].collapse_snow_flower_level_1();
		}
		else if (dis < 1.5*size) {
			pos_y = 4.4*size - dis * 1;
			this->attach = true;
			this->ever_attach = true;
			snow_flower[i].particle_set_1.push_back((void*)this);
			if (snow_flower[i].particle_set_1.size() >= SNOWFLOWER_COLLAPSE_MAX)
				snow_flower[i].collapse_snow_flower_level_1();
		}
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
		if (snow[i].attach == true)
			continue;
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





