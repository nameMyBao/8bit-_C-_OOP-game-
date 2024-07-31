#include "Pickup.h"
#include "Enemy.h"
#include <iostream>

using namespace std;
using namespace sf;

class Skill : public Animation{
private:

	//Spawning and disappearing
	bool Spawned;				// is the pickups spawned
	float Cast_time;			// How long does the skill need to repair before spawn
	float Appear_time;			// How long does the skill appear
	float temp;					// To measure how long the game has run
public:
	Skill(int type);														//Default constructor
	void Cast();												// cast is for the player
	void update(float dt,float gametime,Vector2f pos,Vector2f target);		// for boss
	void draw(RenderWindow& window);										//Draw
	FloatRect getPos();														//get the blobal bounds of the skill
	bool isSpawned();														//Check if the skill is casted 
};