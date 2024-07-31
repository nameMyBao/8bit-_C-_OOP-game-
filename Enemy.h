#pragma once
#include "Animation.h"
#include <iostream>

class Enemy : public Animation
{
private:

	short type;
	Vector2f pos;//position of the enemies
	Vector2f frame;//framesize - width and height
	short status[3]; // 1 health, 2 speed, 3 damage
	bool isDead; //if the enemy is dead or alive

public:
	//Default constructor
	Enemy();
	// Update/Chase the player
	void Chasing(float dt, Vector2f playerpos);
	// when the enemies is hit
	void getHit(short damage);
	// to check if the enemies is dead
	bool dead();
	// draw the enemies
	void draw(RenderWindow& window);
	//set position for the enemies
	void move(float x, float y);
	short get_speed() const;
	//Spawn enemies
	void spawn(Vector2f pos, short level);
	//Get enemy's position
	Vector2f getpos();
	//Get enemy globalbounds for checking collision
	FloatRect getRectPos();
	//Get enemies framesize
	Vector2u getsize();
	//Get enemy damamge
	short get_damage() const;
	//get enemy type
	short get_type() const;
	
};

