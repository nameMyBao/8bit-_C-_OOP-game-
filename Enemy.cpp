#include "Enemy.h"
#include <iostream>

using namespace std;

string enemytexturelocation = "enemy/level1.png";

Enemy::Enemy() : Animation(enemy_framewidth,enemytexturelocation, switchtime)
{
	frame.x = 50;
	frame.y = 50;
	type = NORMAL_ENEMY1;

	isDead = false;
	status[0] = 0;
	status[1] = 0;
	status[2] = 0;

	sprite.setScale(0.5, 0.5);
}

void Enemy::Chasing(float dt,Vector2f playerpos)
{
	if (playerpos.x > pos.x) {
		this->pos.x += status[1] * dt;
	}
	if (playerpos.x < pos.x) {
		this->pos.x -= status[1] * dt;
	}
	if (playerpos.y > pos.y) {
		this->pos.y += status[1] * dt;
	}
	if (playerpos.y < pos.y) {
		this->pos.y -= status[1] * dt;
	}

	sprite.setPosition(pos);

	if (type == 1 || type == 2) {
		double angle = (atan2(playerpos.y - pos.y, playerpos.x - pos.x) * 180.0f) / 3.141;
		sprite.setRotation((float)angle);
	}

	Update(dt);

}

void Enemy::getHit(short damage)
{
	status[0] -= damage;

	if (status[0] < 0) {
		this->isDead = true;
		status[1] = 0;
	}
}

bool Enemy::dead()
{
	return isDead;
}

void Enemy::spawn(Vector2f pos, short type)
{
	isDead = false;

	switch (type)
	{
	case 1:
		//enemy map1
		texture.loadFromFile("enemy/level1.png");

		//status
		status[0] = normal_enemy1_health;
		status[1] = normal_enemy1_speed;
		status[2] = normal_enemy1_damage;
		break;

	case 2:
		//enemy map 2
		texture.loadFromFile("enemy/level2.png");

		//status
		status[0] = normal_enemy2_health;
		status[1] = normal_enemy2_speed;
		status[2] = normal_enemy2_damage;
		break;

	case 10:
		//Boss map 1
		frame.x = boss_framewidth;
		frame.y = boss_frameheight;
		texture.loadFromFile("Boss/level1.png");

		//status
		status[0] = boss1_health;
		status[1] = boss1_speed;
		status[2] = boss1_damage;
		break;

	case 20:
		//Boss map 2
		frame.x = boss_framewidth;
		frame.y = boss_frameheight;
		texture.loadFromFile("Boss/level2.png");

		//status
		status[0] = boss2_health;
		status[1] = boss2_speed;
		status[2] = boss2_damage;
		break;
	}

	this->pos.x = pos.x;
	this->pos.y = pos.y;

	sprite.setTexture(texture);
	sprite.setPosition(pos);
	sprite.setOrigin((float)texture.getSize().x / (unsigned)2, (float)texture.getSize().y / (unsigned)2);

}

Vector2f Enemy::getpos()
{
	return pos;
}

FloatRect Enemy::getRectPos()
{
	return sprite.getGlobalBounds();
}

Vector2u Enemy::getsize()
{
	return texture.getSize();
}

short Enemy::get_damage() const 
{
	return status[2];
}

short Enemy::get_type() const
{
	return this->type;
}

void Enemy::draw(RenderWindow& window)
{
	window.draw(sprite);
}

void Enemy::move(float x, float y)
{
	pos.x = pos.x + x;
	pos.y = pos.y + y;

	sprite.setPosition(pos);
}

short Enemy::get_speed() const {
	return status[1];
}