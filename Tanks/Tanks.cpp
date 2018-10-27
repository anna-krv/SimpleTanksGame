#include "Tanks.h"
#include <E:\2\SFML-2.5.0\include\SFML\Graphics.hpp>
#include <stdexcept>
#include <cmath>
using namespace std;

const float PI = 3.14159265;


Bullet::Bullet(float i_, float j_, float angle_):c(4),i(i_), j(j_), angle(angle_) {
	c.setFillColor(sf::Color::Black);
	c.setOrigin(4, 4);
	c.setPosition(i, j);
}

void Bullet::draw() {
	window.draw(c);
	i +=3*cos(PI*angle/ 180.);
	j += 3 * sin(PI*angle/ 180.);
	if (i >= 500 || j>=500)
		throw exception();
	c.setPosition(i, j);
}

float Bullet::getI() {
	return i;
}

float Bullet::getJ() {
	return j;
}

sf::FloatRect Bullet::getGlobalBounds() {
	return c.getGlobalBounds();
}

Tank::Tank(sf::Color tColor) {
	//coordinates
	i = rand() % 500;
	j = rand() % 500;
	//ellipse
	r.setRadius(11.f);
	r.setOrigin(11, 11);
	r.setScale(2, 1);
	//convex
	convex.setPointCount(3);
	convex.setPoint(0, sf::Vector2f(0, 0));
	convex.setPoint(1, sf::Vector2f(0, 12));
	convex.setPoint(2, sf::Vector2f(36, 0));
	convex.setOrigin(0, 6);

	//texture for tank
	texture->loadFromFile("E:\\2\\SFML_first_Project\\tankTexture.jpg");
	r.setTexture(texture);
	//fill
	convex.setFillColor(tColor);
	r.setFillColor(tColor);
	//outline
	r.setOutlineThickness(0.9);
	r.setOutlineColor(sf::Color(0, 0, 0));
	convex.setOutlineThickness(0.9);
	convex.setOutlineColor(sf::Color(0, 0, 0));
	//setPositions
	r.setPosition(i, j); 
	convex.setPosition(i, j);
}

void Tank::setPos(float dist) {
	float i_ = dist*cos(2 * PI*(r.getRotation()) / 360.);
	float j_ = dist*sin(2 * PI*(r.getRotation()) / 360.);
	if (i+i_<=500 && i+i_>=0)
		i = i + i_;
	if (j + j_ <= 500 && j + j_ >= 0)
		j = j + j_;
	convex.setPosition(i, j);
	r.setPosition(i, j);
}

void Tank::rotate(float x) {
	r.rotate(x);
	convex.rotate(x);
}

void Tank::draw() {
	window.draw(r);
	window.draw(convex);
}

float Tank::getI() {
	return i+29*cos(PI*r.getRotation()/ 180.)+6*sin(PI*r.getRotation()/180.);
}

float Tank::getJ() {
	return j+29*sin(PI*r.getRotation()/ 180.)-6*cos(PI*r.getRotation()/180.);
}

float Tank::getAngle() {
	return r.getRotation();
}

bool Tank::checkCollision(Bullet* b) {
	if (!b)
		return true;
	if (r.getGlobalBounds().intersects(b->getGlobalBounds()))
		return false;
	if (convex.getGlobalBounds().intersects(b->getGlobalBounds()))
		return false;
	return true;
}


Game::Game(sf::Color c1, sf::Color c2) :t1(c1), t2(c2) {
	endMessage.setString("Game Over!");
	endMessage.setFillColor(sf::Color(0, 235, 180));
	endMessage.setOutlineColor(sf::Color(190, 150, 0));
	endMessage.setOutlineThickness(6);
	endMessage.setPosition(50, 150);
}

bool Game::checkConditions() {
	return t1.checkCollision(t2.myBullet) && t2.checkCollision(t1.myBullet);
}

void Game:: run() {
	window.create(sf::VideoMode(500, 500), "Enjoy the Tanks!");
	sf::Font f;
	if (!f.loadFromFile("E:\\2\\SFML_first_Project\\carbontype.ttf")) {}
	endMessage.setCharacterSize(54);
	endMessage.setFont(f);
	while (window.isOpen()){
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();

			//for First Tank
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				t1.rotate(-15);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				t1.rotate(15);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				t1.setPos(10);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				t1.setPos(-10);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
				t1.myBullet = new Bullet(t1.getI(), t1.getJ(), t1.getAngle());

			//for Second Tank
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				t2.rotate(-15);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
				t2.rotate(15);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
				t2.setPos(10);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				t2.setPos(-10);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
				t2.myBullet=new Bullet(t2.getI(), t2.getJ(), t2.getAngle());
		}

		window.clear(sf::Color(240,240,240));

		if (checkConditions()) {
			t1.draw(); t2.draw();
			if (t1.myBullet) {
				try { t1.myBullet->draw(); }
				catch (exception) { t1.myBullet = nullptr; }
			}
			if (t2.myBullet) {
				try { t2.myBullet->draw(); }
				catch (exception) { t2.myBullet = nullptr; }
			}
		}
		else {
			window.draw(endMessage);
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::KeyPressed || event.type == sf::Event::Closed)
					window.close();
			}
		}
		window.display();
	}
	
}
