#include "Skill.h"

string skill_texture = "Skills/level1.png";
Skill::Skill(int type)
{
	if (type == 10) {
		texture.loadFromFile("Skills/level1.png");
	}
	else {
		texture.loadFromFile("Skills/level2.png");
	}
	sprite.setTexture(texture);
	sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);

	Cast_time = 1.0f;
	Appear_time = 0.5f;
	temp = 0;
	Spawned = false;
}

void Skill::Cast()
{
	Spawned = true;
	texture.loadFromFile("Skills/main.png");
	sprite.setTexture(texture);

}

void Skill::update(float dt,float gametime, Vector2f pos,Vector2f target)
{

	if (Spawned == true)
	{
		temp +=dt;
	}
	
	if (gametime > Cast_time)
	{
		Spawned = true;
		Cast_time += Cast_time;
	}

	if (temp > Appear_time && Spawned == true) {
		temp = 0;
		Spawned = false;
	}
	Vector2f pos1; pos1.x = 0; pos1.y = 0;
	srand(gametime);

	if (pos.x > target.x) {
		pos1.x = pos.x - (float)(rand() % 200) ;
	}
	else
		pos1.x = pos.x + (float)(rand() % 200);

	if (pos.y > target.y) {
		pos1.y = pos.y - (float)(rand() % 200);
	}
	else
		pos1.y = pos.y + (float)(rand() % 200);

	sprite.setPosition(pos1);

	//Update(dt);
}

void Skill::draw(RenderWindow& window)
{
	window.draw(sprite);
}

FloatRect Skill::getPos()
{
	return sprite.getGlobalBounds();
}

bool Skill::isSpawned()
{
	return Spawned;
}
