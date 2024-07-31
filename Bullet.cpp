#include "Bullet.h"

string bullet = "char/bullet.png";

Bullet::Bullet() : Animation(bullet_framewidth,bullet,switchtime)
{
	this->texture.loadFromFile("char/bullet.png");
	sprite.setTexture(texture);

	inflight = false;
	flightspeed = bullet_speed;

	speedX = 0;
	speedY = 0;

	minDistance.x = 0; minDistance.y = 0;
	maxDistance.x = 0; maxDistance.y = 0;
}

void Bullet::stop()
{
	inflight = false;
}

bool Bullet::isinflight()
{
    return inflight;
}

void Bullet::shoot(Player player)
{
	float alpha = 0;
	Vector2f target = Vector2f(0,0);
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		target.x = player.getpos().x - 1000;
		speedX = flightspeed;
		alpha = 180 ;
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		target.x = player.getpos().x + 1000;
		speedX = flightspeed;
	}
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		target.y = player.getpos().y - 1000;
		speedY = flightspeed;
		alpha = 270;
	}
	if(Keyboard::isKeyPressed(Keyboard::Down)) {
		target.y = player.getpos().y + 1000;
		speedY = flightspeed;
		alpha = alpha + 90;
	}
	if (Keyboard::isKeyPressed(Keyboard::Down)&&Keyboard::isKeyPressed(Keyboard::Left)){
		alpha = 135;
	}
	if (Keyboard::isKeyPressed(Keyboard::Down)&&Keyboard::isKeyPressed(Keyboard::Right)){
		alpha = 45;
	}
	if (Keyboard::isKeyPressed(Keyboard::Up)&&Keyboard::isKeyPressed(Keyboard::Left)){
		alpha = -135;
	}
	if (Keyboard::isKeyPressed(Keyboard::Up)&&Keyboard::isKeyPressed(Keyboard::Right)){
		alpha = -45;
	}
	inflight = true;

	this->pos.x = player.getpos().x;
	this->pos.y = player.getpos().y;

	//Position the bullet ready to be drawn
	sprite.setPosition(pos);
	sprite.setRotation(alpha);

	//Set the speed on x and y axis to make the bullet shoot smoothly

	// Point the bullet in the right direction
	if (target.x < pos.x)
	{
		speedX *= -1;
	}
	if (target.y < pos.y)
	{
		speedY *= -1;
	}

	//Set a max range of 1000 pixels
	float range = 1000;
	minDistance.x = pos.x - range;
	minDistance.y = pos.y - range;

	maxDistance.x = pos.x + range;
	maxDistance.y = pos.y + range;
}

FloatRect Bullet::getPos()
{
    return sprite.getGlobalBounds();
}

void Bullet::Flying(float dt)
{
	//Update the pos
	this->pos.x += speedX * dt;
	this->pos.y += speedY * dt;

	sprite.setPosition(pos);

	if (pos.x < minDistance.x || pos.x > maxDistance.x || pos.y < minDistance.y || pos.y > maxDistance.y) {
		inflight = false;
	}

}

void Bullet::draw(RenderWindow& window)
{
	window.draw(sprite);
}
