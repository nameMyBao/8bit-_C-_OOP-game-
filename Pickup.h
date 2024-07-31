#pragma once
#include "Animation.h"
class Pickup : public Animation
{
protected:

	//Status
	short Status;
	//Spawning and disappearing
	bool Spawned;				// is the pickups spawned
	float SecondsSinceSpawn;	// The moment when the pick up is spawned
	float SecondsSinceDeSpawn;	// The moment when the pick up disappear
	float SecondsToLive;		// How long is pickup appear on the window once
	float SecondsToWait;		// How long will the pick up appear again after it disappear
public:
	//Constructor
	Pickup();
	//Prepare the pickup
	void spawn(RenderWindow& window);
	//Check the pos of a pickup
	FloatRect getPos();
	//Draw to the window
	void draw(RenderWindow& window);
	//Update
	void update(float dt, RenderWindow& window);
	//When the player pick it up
	short picked_up();
	//Check if it spawned
	bool isSpawned();
};

