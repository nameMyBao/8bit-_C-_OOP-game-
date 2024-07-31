#include "Player.h"

string chartexturelocation = "char/main.png";

Player::Player() : Animation(player_framewidth,chartexturelocation, switchtime)
{
	dead = false;
	faceright = true;
	direction = false;

	texture.loadFromFile("char/main.png");
	sprite.setTexture(texture);
	frameheight = texture.getSize().y;

	sprite.setOrigin((float)player_framewidth / 2.0f, (float)frameheight / 2.0f);
	sprite.setPosition(777,786);
	sprite.setScale(0.5, 0.5);

	type_of_movement = 1;
	Health = 150;
	Damage = 70;
	Speed = 100;
}

void Player::Reset()
{
	Health = 152;
	Damage = 50;
	Speed = 200;
}

void Player::Moving(float deltatime,RenderWindow& window)
{
	Vector2f pos;
	pos.x = 0.0;
	pos.y = 0.0;

	//walk
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
			pos.x -= Speed * deltatime;
			type_of_movement = 1;
			faceright = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::Right)) {
			pos.x += Speed * deltatime;
			type_of_movement = 1;
			faceright = true;
	}

	//walk up and down
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		pos.y -= Speed * deltatime;
		type_of_movement = 1;
		direction = true;

	}
	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		pos.y += Speed * deltatime;
		type_of_movement = 1;
		direction = true;
	}

	//attack
	if (Keyboard::isKeyPressed(Keyboard::C)) {
		type_of_movement = 2;
	}

	sprite.move(pos);
	Update(deltatime);

	//dead 
	if (dead == true) {
		type_of_movement = 0;
	}
}

void Player::draw(RenderWindow& window)
{
	switch (type_of_movement)
	{
	case 0:
		texture.loadFromFile("char/maindead.png");
		break;
	case 1:
		texture.loadFromFile("char/main.png");
		break;
	case 2:
		texture.loadFromFile("char/mainattack.png");
		break;
	}

	sprite.setTexture(texture);

	window.draw(sprite);
}

bool Player::get_faceright()
{
	return faceright;
}

bool Player::get_direction()
{
	return this->direction;
}

Vector2f Player::getpos()
{
	return sprite.getPosition();
}

FloatRect Player::getRectPos()
{
	return sprite.getGlobalBounds();
}

void Player::hit(Time hittime,short damage)
{
	if (hittime.asMilliseconds() - lasthit.asMilliseconds() > 1000) {
		lasthit = hittime;
		set_health(damage);
	}
}

Time Player::getlasthittime()
{
	return lasthit;
}

short Player::get_health() const
{
	return Health;
}

short Player::get_damage() const
{
	return this->Damage;
}

short Player::get_speed() const
{
	return this->Speed;
}

Vector2f Player::getsize()
{
	return Vector2f(player_framewidth,frameheight);
}

bool Player::isdead()
{
	if (this->Health <= 0) {
		return true;
	}
	return false;
}

void Player::set_health(unsigned short damage)
{
	this->Health -= damage;
}

void Player::set_damage(unsigned short damage)
{
	this->Damage += damage;
}

void Player::set_speed(unsigned short speed)
{
	this->Speed += speed;
}

void Player::pick_up(short value)
{
	this->Health += value;
}

void Player::move(Vector2f pos)
{
	pos.x += this->getpos().x;
	pos.y += this->getpos().y;
	sprite.setPosition(pos);
}

void Player::update(Player player, float deltatime)
{
	Vector2f pos;
	pos.x = 0.0;
	pos.y = 0.0;

	//walk
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		pos.x += Speed * deltatime;
		type_of_movement = 1;
		faceright = true;
	}

	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		pos.x -= Speed * deltatime;
		type_of_movement = 1;
		faceright = false;
	}

	//walk up and down
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		pos.y += Speed * deltatime;
		type_of_movement = 1;
		direction = false;

	}
	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		pos.y -= Speed * deltatime;
		type_of_movement = 1;
		direction = false;
	}
	sprite.move(pos);
	Update(deltatime);

}




