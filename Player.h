#pragma once
#include <iostream>
#include "Animation.h"
#include "Pickup.h"

using namespace std;

class Player : public Animation 
{
protected :
	short Health, Speed, Damage; //status 

	bool dead; // the player is dead or not 
	bool direction; // true is up vice versa
	Time lasthit;// the last time the character was hit

	int type_of_movement;//1 is walk, 2 is attack

public: 

	//Default constructor
	Player();
	//Reset the status of the player to default
	void Reset();
	//Manipulate the player
	void Moving(float deltatime,RenderWindow& window);
	//draw the player to the window
	void draw(RenderWindow& window);
	//get the direction left or right, up or down 
	bool get_faceright();
	bool get_direction();
	//get player position and size
	Vector2f getpos();
	Vector2f getsize();
	//get the sprite global pounds
	FloatRect getRectPos();
	//if the player is hit 
	void hit(Time hittime,short damage);
	//get the last time the player was hit
	Time getlasthittime();
	// for the status
	short get_health() const;
	short get_damage() const;
	short get_speed() const;
	//check if the player is dead or alive
	bool isdead();
	//set the status
	void set_health(unsigned short damage);
	void set_damage(unsigned short damage);
	void set_speed(unsigned short speed);
	//if the player collide with the pickups
	void pick_up(short value);
	//can be understand as set pos for the player
	void move(Vector2f pos);
	void update(Player player, float deltatime);
	

};

