#include "Pickup.h"

string pickup_texture = "Pickups/health.png";

Pickup::Pickup() : Animation(pickup_framewidth,pickup_texture,switchtime)
{
	texture.loadFromFile("Pickups/health.png");
	this->Status = 30;

	sprite.setTexture(texture);
	sprite.setOrigin(texture.getSize().x/2.0f, texture.getSize().y / 2.0f);
	sprite.setScale(5, 5);
	
	SecondsToLive = START_SECONDS_TO_WAIT;
	SecondsToWait = START_WAIT_TIME;
	SecondsSinceDeSpawn = 0;
	SecondsSinceSpawn = 0;
	Spawned = false;
}

void Pickup::spawn(RenderWindow& window)
{
	Spawned = true;

	srand((int)time(NULL));
	//Random locatiom
	float x = (float)(rand() % (window.getSize().x));
	float y = (float)(rand() % (window.getSize().y));
	
	SecondsSinceSpawn = 0;

	sprite.setPosition(x, y);
}

FloatRect Pickup::getPos()
{
	return sprite.getGlobalBounds();
}

void Pickup::draw(RenderWindow& window)
{
	window.draw(sprite);
}

void Pickup::update(float dt,RenderWindow& window)
{
	if (Spawned == true)
	{
		SecondsSinceSpawn += dt;
	}
	else
	{
		SecondsSinceDeSpawn += dt;
	}
	// Do we need to hide a pickup?
	if (SecondsSinceSpawn > SecondsToLive && Spawned == true)
	{
		// Remove the pickup and put it somewhere else
		Spawned = false;
		SecondsSinceDeSpawn = 0;
	}
	// Do we need to spawn a pickup
	if (SecondsSinceDeSpawn > SecondsToWait && !Spawned)
	{// spawn the pickup and reset the timer
		spawn(window);
	}

	Update(dt);
}

short Pickup::picked_up()
{
	SecondsSinceDeSpawn = 0;

	Spawned = false;

	return this->Status;
}

bool Pickup::isSpawned()
{
	return Spawned;
}
