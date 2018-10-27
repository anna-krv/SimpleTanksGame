#pragma once
#include <E:\2\SFML-2.5.0\include\SFML\Graphics.hpp>
#include <iostream>
using namespace std;
static sf::RenderWindow window;


class Bullet {
private:
	float i, j; //coordinates
	sf::CircleShape c;
	float angle;
public:
	Bullet(float i_, float j_, float angle_);
	void draw();
	float getI();
	float getJ();
	sf::FloatRect getGlobalBounds();
};

class Tank {
private:
	float i, j; //coordinates
	sf::CircleShape r; //ellipse
	sf::ConvexShape convex; //
	//let it be for safety)!
	sf::Texture* texture=new (sf::Texture);
public:
	void rotate(float x);
	Tank(sf::Color tColor);
	void setPos(float dist);
	void draw();
	float getI(); float getJ(); //from whete the bullet comes
	float getAngle();
	//Stupid!!!!!!!!!!
	Bullet *myBullet = nullptr;
	bool checkCollision(Bullet* b);
};


class Game {
private:
	Tank t1, t2;
	bool checkConditions();
	sf::Text endMessage;
public:
	Game(sf::Color c1, sf::Color c2);
	void run();
};

