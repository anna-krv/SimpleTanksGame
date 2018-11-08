#pragma once
#include <E:\2\SFML-2.5.0\include\SFML\Graphics.hpp>
#include <iostream>
using namespace std;
static sf::RenderWindow window;


class Bullet {
private:
	int id;//number of tank from which 
	        //the bullet was created
	float i, j; //coordinates
	sf::CircleShape c;
	float angle;
public:
	Bullet(float i_, float j_, float angle_, int id_);
	int getId() const;
	void draw();
	void setPos();
	float getI();
	float getJ();
	sf::FloatRect getGlobalBounds() const;
};

class Tank {
private:
	//overall number of tanks in a game
	static int numberOfTanks;
	int id; //number of our tank
	float i, j; //coordinates
	sf::CircleShape r; //ellipse
	sf::ConvexShape convex; //
	//let it be for safety)!
	sf::Texture* textureTank=new (sf::Texture);
	sf::Texture* textureCannon = new (sf::Texture);
public:
	void display();
	void random();
	void rotate(float x);
	int getId() const;
	Tank(sf::Color tColor_);
	sf::Color tColor;
	void setPos(float dist);
	void draw();
	float getI(); float getJ(); //from whete the bullet comes
	float getAngle();
	bool checkCollision(const Bullet& b) const;
};


class Game {
private:
	int state = 0; //0- start, 1- main, 2- end
	vector<Bullet> bullets;
	Tank t1, t2;
	void checkConditions();
	sf::Text endMessage;
public:
	Game(sf::Color c1, sf::Color c2);
	void run();
};

