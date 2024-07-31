#pragma once
#include "Animation.h"
#include "Player.h"

class Bullet : public Animation
{
	Vector2f pos; // current position of the bullet

	bool inflight;// is the bullet flying or not
	float flightspeed;// bullet's speed

	float speedX;//bullet's speed on x axis 
	float speedY;//bullet's speed on y axis

	//A border - maximum range that the bullet can fly away
	Vector2f minDistance;
	Vector2f maxDistance;

public:
	//Constructor
	Bullet();
	//Stop the bullet when it collide or touch its border
	void stop();
	//is the bullet still in flight
	bool isinflight();
	//shoot the bullet
	void shoot(Player player);
	//get the globalbounds for collision
	FloatRect getPos();
	//Update the bullet
	void Flying(float dt);
	//Draw the bullet
	void draw(RenderWindow& window);
};

