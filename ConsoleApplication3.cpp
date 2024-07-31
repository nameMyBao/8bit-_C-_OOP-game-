#include <iostream>
#include "Player.h"
#include "Enemy.h"
#include <cstdlib>
#include "Bullet.h"
#include "Pickup.h"
#include "Skill.h"
#include "Animation.h"
#include "background.h"

using namespace std;
using namespace sf;

//Create enemies horde
Enemy* horde(int amount, int type) {
	Enemy* enemies = new Enemy[amount];

	for (int i = 0; i < amount; i++) {
		srand(int(time(NULL)) * i);

		Vector2f pos;
		pos.x = (float)(rand() % 801 )+ 200;
		pos.y = (float)(rand() % 600 )+ 100;

		enemies[i].spawn(pos, type);
	}
	return enemies;
}

//Make the view resizalbe
void ResizeView(RenderWindow& window, View& view) {
	float ratio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(viewheight * ratio, viewheight);
}

int main()
{
	//window and view
	RenderWindow window(VideoMode(920, 800), "Finding Memo", Style::Resize | Style::Close);
	View view(Vector2f(viewwidth, viewheight), Vector2f(viewwidth, viewheight));

	//Font and Texts
	Font font;
	font.loadFromFile("Text/font.tff");
	//Health bar
	RectangleShape healthBar;
	healthBar.setFillColor(Color::Red);

	//alert
	Text alert; alert.setString("Boss's skill is spawned"); 
	alert.setFont(font); alert.setCharacterSize(30);
	alert.setFillColor(Color::Black);
	/*
	Texture skill; skill.loadFromFile("SKills/level1.png");
	Sprite Skills; Skills.setTexture(skill); Skills.setOrigin(skill.getSize().x/2.0f, skill.getSize().y / 2.0f);
	*/
	//Create the player
	Player player1;

	Time gametime,dashtimer,movetimer;
	Clock clock;

	//temp position
	Vector2f pos;		Vector2f pos1;
	pos.x = 0;			pos1.x = 0;
	pos.y = 0;			pos1.y = 0;

	//////////////////////////////Create horde//////////////////////////
	int numenemies = 10, aliveenemies = numenemies;
	Enemy* enemies = nullptr;
	delete[] enemies;
	enemies = horde(numenemies, 1);
	////////////////////////////////////////////////////////////////////
	
	////////////////Create Boss///////////////////////
	Enemy Boss;
	Boss.spawn(Vector2f(600.0f, 600.0f), 10);
	float dtime=0;
	/////////////////////////////////////////////////

	/////////////////////////Bullet//////////////////
	int numberbullet = 40;
	Bullet* bullet = new Bullet[40];
	Time lastPressed;
	int i1 = 0;
	float firerate = 1;
	/////////////////////////////////////////////////
	
	//////////////////////some pickup//////////////////////
	Pickup health;
	///////////////////////skill//////////////////////////
	Skill boss1(10);


	////////////////////////////////////Map///////////////////////////////////////
	vector<vector<Vector2i >> map1;
	Sprite tile1;
	Texture tileTexture1;
	tileTexture1.loadFromFile("baihatcuatoi.png");
	tile1.setTexture(tileTexture1);

	vector<vector<int >> colmap1;

	createbackground("tinhyeuhoctro.txt", map1);
	//set colision 
	setcoli("colisiontinhyeu.txt", colmap1);

	RectangleShape coli (Vector2f(50, 50));
	/////////////////////////////////////////////////////////////////////////////
	
	//Game loop
	while (window.isOpen())
	{
		//Deltatime and gametotaltime
		Time dt = clock.restart();
		gametime += dt;
		dtime = dt.asSeconds();

		//Skills.setPosition(player1.getpos());
		alert.setPosition(Vector2f(player1.getpos().x, player1.getpos().y - 50));

		// size up the health bar
		healthBar.setSize(Vector2f(player1.get_health() / 3.0f, 10.0f));
		healthBar.setOrigin(healthBar.getSize().x / 2.0f, healthBar.getSize().y / 2.0f);
		healthBar.setPosition(player1.getpos()+Vector2f(0.0f,-30.0f));

		Event ev;
		//Event polling
		while (window.pollEvent(ev))
		{
			switch (ev.type)
			{
			case Event::Closed:
				window.close();
				break;
			case Event::Resized:
				ResizeView(window, view);
				break;
			case Event::KeyPressed:
				if (ev.key.code == Keyboard::Escape)
					window.close();
				break;
			case Event::TextEntered:
				if (ev.text.unicode < 128) {};
				break;
			}
		}

		//set the viewcentre
		view.setCenter(player1.getpos());

		//Fire the bullet
		if (Keyboard::isKeyPressed(Keyboard::C)) {
			if (gametime.asMilliseconds() - lastPressed.asMilliseconds() > 500 / firerate) {
				//shoot the bullet
				if (i1 > numberbullet)
					i1 = 0;

				bullet[i1].shoot(player1);
				lastPressed = gametime;
				i1++;
			}
		}

		//Update the bullet
		for (int i = 0; i < 40; i++) {
			bullet[i].Flying(dt.asSeconds());
		}

		//Update the pickup
		health.update(dt.asSeconds(),window);

		//Update the skill
		boss1.update(dtime,gametime.asSeconds(), Boss.getpos(),player1.getpos());

		//Update the player
		player1.Moving(dt.asSeconds(),window);

		//Let Enemies chase the player
		if (Boss.dead() == false) {
			//Boss.Chasing(dt.asSeconds(), player1.getpos());

			if (player1.getpos().x > Boss.getpos().x) {
				pos1.x += 40 * dtime;
			}
			if (player1.getpos().x < Boss.getpos().x) {
				pos1.x -= 40 * dtime;
			}
			if (player1.getpos().y > Boss.getpos().y) {
				pos1.y += 40 * dtime;
			}
			if (player1.getpos().y < Boss.getpos().y) {
				pos1.y -= 40 * dtime;
			}
			Boss.move(pos1.x, pos1.y);
			pos1.x = 0; pos1.y = 0;
		}

		//Update the enemies
		for (int i = 0; i < numenemies; i++) {
			if (enemies[i].dead() == false) {
				enemies[i].Chasing(dt.asSeconds(), player1.getpos());
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Z)) {
			if (gametime.asMilliseconds() - dashtimer.asMilliseconds() > 500) {

				if (Keyboard::isKeyPressed(Keyboard::Left)) {
					pos.x -= 100*player1.get_speed()*dt.asSeconds();
					cout << pos.x <<"left"<<endl;
				}
				if (Keyboard::isKeyPressed(Keyboard::Right)) {
					pos.x += 100 * player1.get_speed() * dt.asSeconds();
					cout << pos.x << "right" << endl;
				}
				if (Keyboard::isKeyPressed(Keyboard::Up)) {
					pos.y -= 100 * player1.get_speed() * dt.asSeconds();
					cout << pos.y << "up" << endl;
				}
				if (Keyboard::isKeyPressed(Keyboard::Down)) {
					pos.y += 100 * player1.get_speed() * dt.asSeconds();
					cout << pos.y << "down" << endl;
				}

				dashtimer = gametime;
				player1.move(pos);
				pos.x = 0; pos.y = 0;
			}
		}


		/// ///////////////////////////////////////////////////////////////

		window.clear();

		// Draw the colision map
		for (int i = 0; i < colmap1.size(); i++)
		{
			for (int j = 0; j < colmap1[i].size(); j++)
			{
				if (colmap1[i][j] == 1)
				{
					Vector2f pos((float)(j * 50),(float)(i * 50));
					coli.setPosition(pos);
					window.draw(coli);
					if (player1.getRectPos().intersects(coli.getGlobalBounds()))
					{
						player1.update(player1, dt.asSeconds());
					}
				}
			}
		}

		//Draw the map1
		for (int i = 0; i < map1.size(); i++)
		{
			for (int j = 0; j < map1[i].size(); j++)
			{
				if (map1[i][j].x != -1 && map1[i][j].y != -1)
				{
					tile1.setPosition((float)(j * 50),(float)(i * 50));
					tile1.setTextureRect(IntRect(map1[i][j].x * 50, map1[i][j].y * 50, 50, 50));
					window.draw(tile1);
				}
			}
		}


		//Draw the enemies
		for (int i = 0; i < numenemies; i++)
		{
			if (enemies[i].dead() == false) {
				enemies[i].draw(window);
			}
		}

		if (Boss.dead() == false)
			Boss.draw(window);

		//Draw the bullet
		for (int i = 0; i < 40; i++) {
			if (bullet[i].isinflight() == true) {
				bullet[i].draw(window);
			}
		}

		//Draw the pickups
		if (health.isSpawned() == true)
		{
			health.draw(window);
		}

		if (boss1.isSpawned() == true) {
			boss1.draw(window);
		}

		player1.draw(window);

		////////////////////////////////////////Collision detection////////////////////////////////////
		//Bullet and enemies
		for (int i = 0; i < 40; i++)
		{
			for (int j = 0; j < numenemies; j++)
			{
				if (bullet[i].isinflight() && enemies[j].dead() == false)
				{
					if (bullet[i].getPos().intersects(enemies[j].getRectPos()))
					{
						// Stop the bullet
						bullet[i].stop();
						// Register the hit and see if it was a kill
						enemies[j].getHit(player1.get_damage());
					}

				}
			}
		}
		for (int i = 0; i < 40; i++) {
			if (bullet[i].isinflight() && Boss.dead() == false) {
				if (bullet[i].getPos().intersects(Boss.getRectPos()))
				{
					// Stop the bullet
					bullet[i].stop();
					// Register the hit and see if it was a kill
					Boss.getHit(player1.get_damage());
				}
			}
		}

		//Enemies and Player
		for (int i = 0; i < numenemies; i++)
		{
			if (player1.getRectPos().intersects(enemies[i].getRectPos()) && enemies[i].dead() == false)
			{
				player1.hit(gametime, enemies[i].get_damage());
			}
		}

		//Enemies and Boss
		for (int i = 0; i < numenemies; i++) {
			if (Boss.getRectPos().intersects(enemies[i].getRectPos()) && Boss.dead()==false && enemies[i].dead()==false) {
				if (Boss.getpos().x > enemies[i].getpos().x) {
					enemies[i].move(-1, 0);
				}
				if (Boss.getpos().x < enemies[i].getpos().x) {
					enemies[i].move(1, 0);
				}
				if (Boss.getpos().y > enemies[i].getpos().y) {
					enemies[i].move(0, -1);
				}
				if (Boss.getpos().y < enemies[i].getpos().y) {
					enemies[i].move(0, 1);
				}
			}

		}

		//Enemies and Enemies
		for (int i = 0; i < numenemies; i++)
		{
			for (int j = i; j < numenemies; j++)
			{
				if (enemies[i].dead() == false && enemies[j].dead() == false) {
					if (enemies[i].getRectPos().intersects(enemies[j].getRectPos())) {
						if (enemies[i].getpos().x > enemies[j].getpos().x) {
							enemies[i].move(1, 0);
							enemies[j].move(-1, 0);
						}
						if (enemies[i].getpos().x < enemies[j].getpos().x) {
							enemies[i].move(-1, 0);
							enemies[j].move(1, 0);
						}
						if (enemies[i].getpos().y > enemies[j].getpos().y) {
							enemies[i].move(0, 1);
							enemies[j].move(0, -1);
						}
						if (enemies[i].getpos().y < enemies[j].getpos().y) {
							enemies[i].move(0, -1);
							enemies[j].move(0, 1);
						}
					}
				}
			}
		}

		//Player and the pickups
		if (player1.getRectPos().intersects(health.getPos()) && health.isSpawned())
		{
			player1.pick_up(health.picked_up());

		}
		//Skill and the player
		if (player1.getRectPos().intersects(boss1.getPos()) && boss1.isSpawned())
		{
			player1.hit(gametime,50);

		}

		//window.draw(Skills);

		window.draw(healthBar);
		window.setView(view);
		window.display();
		//Close
		if (player1.isdead() == true) {
			window.close();
		}
	}
	return 0;
}

