#include "Animation.h"

Animation::Animation(){
	totalframe = 0;
	currentframe = 0;
	totaltime = 0;
	switchtime = 0;
	framewidth = 50;
	frameheight = 50;
	faceright = true;
}

Animation::Animation(const short framewidth, string& texturelocation, float switchtime){
	this->switchtime = switchtime;

	totaltime = 0.0;
	currentframe = 0;
	faceright = true;
	texture.loadFromFile(texturelocation);
	totalframe = texture.getSize().x / framewidth;

	this->framewidth = framewidth;
	this->frameheight = player_frameheight;

}

void Animation::Update(float gametime) {
	totaltime += gametime;//assign gametime to totaltime

	//Changing the frame
	if (totalframe != 1) {
		while (totaltime >= switchtime) {
			totaltime -= switchtime;
			//Make it back to the first frame after finish a movement
			if (currentframe >= totalframe) {
				currentframe = 0;
			}
			else
				currentframe = (1 + currentframe) % totalframe;// move to the next frame but just during totalframe
		}
		totaltime++;
	}

	if (faceright)
	{
		sprite.setTextureRect(sf::IntRect(currentframe * framewidth, 0, framewidth, texture.getSize().y));
	}
	else
	{
		//Read the texture from right to left using negative numbers.
		sprite.setTextureRect(sf::IntRect(framewidth * (1 + currentframe), 0, -framewidth, texture.getSize().y));
	}
}
