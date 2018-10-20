#pragma once
#include <E:\2 курс лабки\SFML-2.5.0\include\SFML\Graphics.hpp>

static sf::RenderWindow window;


class Tank {
private:
	int i, j; //coordinates
	sf::RectangleShape r;
	sf::ConvexShape convex;
public:
	Tank(sf::Color tColor);
	void setPos(int i, int j);
	void draw();
};


class Game {
public:
	void run();
};

