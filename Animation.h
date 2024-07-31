#pragma once
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "Constant.h"
using namespace sf;
using namespace std;

class Animation {
protected:
	short totalframe; //is the number of drawing in a picture
	short currentframe; // is the current drawing in the movement
	short framewidth, frameheight; // the size of the frame 

	//totaltime can be as the gametime which is how long has the game run
	//switchtime is for changing the frame
	float totaltime,switchtime;

	//Direction of the movement 
	bool faceright;

	Texture texture;
	Sprite sprite;

public:

	Animation();
	Animation(const short framewidth, string& texturelocation, float switchtime);
	// Make the effect
	//deltatime is the time between two images
	void Update(float deltatime);
};
