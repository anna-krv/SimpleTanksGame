#include "Tanks.h"
#include <E:\2 курс лабки\SFML-2.5.0\include\SFML\Graphics.hpp>


Tank::Tank(sf::Color tColor):r(sf::Vector2f(36, 20)) {
	i = rand() % 500, j = rand() % 500;

	//convex
	convex.setPointCount(8);
	int ii = i + 10, jj = j + 2;
	convex.setPoint(0, sf::Vector2f(ii+8, jj));
	convex.setPoint(1, sf::Vector2f(ii, jj+5));
	convex.setPoint(2, sf::Vector2f(ii, 11+jj));
	convex.setPoint(3, sf::Vector2f(8+ii, 16+jj));
	convex.setPoint(4, sf::Vector2f(16+ii, 11+jj));
	convex.setPoint(5, sf::Vector2f(37+ii, 11+jj));
	convex.setPoint(6, sf::Vector2f(37+ii, 5+jj));
	convex.setPoint(7, sf::Vector2f(16+ii, jj+5));

	//fill
	r.setFillColor(tColor); 
	convex.setFillColor(tColor);
	//outline
	r.setOutlineThickness(1); 
	r.setOutlineColor(sf::Color(0, 0, 0)); 
	convex.setOutlineThickness(1);
	convex.setOutlineColor(sf::Color(0, 0, 0));
	
	r.setPosition(i, j); 
}

void Tank::setPos(int i_, int j_) {
	i =(i+500+ i_)%500; j =(j+500+ j_)%500;
	r.setPosition(i, j); 
	int ii = i + 10, jj = j + 2;
	convex.setPoint(0, sf::Vector2f(ii + 8, jj));
	convex.setPoint(1, sf::Vector2f(ii, jj + 5));
	convex.setPoint(2, sf::Vector2f(ii, 11 + jj));
	convex.setPoint(3, sf::Vector2f(8 + ii, 16 + jj));
	convex.setPoint(4, sf::Vector2f(16 + ii, 11 + jj));
	convex.setPoint(5, sf::Vector2f(37 + ii, 11 + jj));
	convex.setPoint(6, sf::Vector2f(37 + ii, 5 + jj));
	convex.setPoint(7, sf::Vector2f(16 + ii, jj + 5));
}

void Tank::draw() {
	window.draw(r);
	window.draw(convex);
}

void Game:: run() {
	window.create(sf::VideoMode(500, 500), "First SFML Game!");
	Tank t1(sf::Color(0,255,0)), t2(sf::Color(255,0,0));
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			//for First Tank
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				t1.setPos(-10, 0);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				t1.setPos(10, 0);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				t1.setPos(0, -10);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				t1.setPos(0, 10);

			//for Second Tank
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				t2.setPos(-10, 0);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
				t2.setPos(10, 0);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
				t2.setPos(0, -10);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				t2.setPos(0, 10);


		}

		window.clear(sf::Color(200,200,200));

		t1.draw(); t2.draw();

		window.display();
	}
}