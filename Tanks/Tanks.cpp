#include "Tanks.h"
#include <E:\2\SFML-2.5.0\include\SFML\Graphics.hpp>
#include <stdexcept>
#include <ctime>
#include <cstdlib>
#include <cmath>
using namespace std;

const float PI = 3.14159265;
int Tank:: numberOfTanks = 0;

Bullet::Bullet(float i_, float j_, float angle_, int id_):c(5),i(i_), j(j_), angle(angle_), id(id_) {
	c.setFillColor(sf::Color::Black);
	c.setOrigin(5, 5);
	c.setPosition(i, j);
}

//post: throws exception if bullet is outside the screen
void Bullet::setPos() {
	i += 2 * cos(PI*angle / 180.);
	j += 2 * sin(PI*angle / 180.);
	if (i >= 500 || j >= 500 || i <= 0 || j <= 0)
		throw exception();
	c.setPosition(i, j);
}

//post: throws exception if bullet is outside the screen
void Bullet::draw() {
	window.draw(c);
	setPos();
}

int Bullet::getId() const{
	return id;
}

float Bullet::getI() {
	return i;
}

float Bullet::getJ() {
	return j;
}

sf::FloatRect Bullet::getGlobalBounds() const{
	return c.getGlobalBounds();
}


void Tank::display() {
	i = 100+300*(id-1); j=320;
	r.setPosition(i, j); convex.setPosition(i, j);
	r.setScale(3.4, 2); convex.setScale(2, 2);
}

void Tank::random() {
	srand(time(NULL)+id*30282);
	i = rand()%500; j =rand()%500;
	r.setPosition(i, j); convex.setPosition(i, j);
	r.setScale(1.7, 1); convex.setScale(1, 1);
}

Tank::Tank(sf::Color tColor_):id(++numberOfTanks), tColor(tColor_){
	//ellipse
	r.setRadius(17.f);
	r.setOrigin(17, 17);
	r.setScale(1.7, 1.);
	//convex
	convex.setPointCount(4);
	convex.setPoint(0, sf::Vector2f(0, 7));
	convex.setPoint(1, sf::Vector2f(40, 0));
	convex.setPoint(2, sf::Vector2f(40, 20));
	convex.setPoint(3, sf::Vector2f(0, 13));
	convex.setOrigin(0, 10);
	//texture for tank
	textureTank->loadFromFile("E:\\2\\SFML_first_Project\\tankTexture.jpg");
	r.setTexture(textureTank); 
	//texture for tank
	textureCannon->loadFromFile("E:\\2\\SFML_first_Project\\cannonTexture.jpg");
	convex.setTexture(textureCannon);
	//colors
	r.setFillColor(tColor);
	convex.setOutlineColor(sf::Color::Black);
	convex.setOutlineThickness(1.2);
	convex.setFillColor(sf::Color(205, 205, 0, 230)); 
	rotate(180 * (id + 1));
}

void Tank::setPos(float dist) {
	float i_ = dist*cos(PI*(convex.getRotation()) / 180.);
	float j_ = dist*sin(PI*(convex.getRotation()) / 180.);
	if (i+i_<=500 && i+i_>=0)
		i = i + i_;
	if (j + j_ <= 500 && j + j_ >= 0)
		j = j + j_;
	convex.setPosition(i, j);
	r.setPosition(i, j);
}

void Tank::rotate(float x) {
	convex.rotate(x);
}

void Tank::draw() {
	window.draw(r);
	window.draw(convex);
}

float Tank::getI() {
	return i+40*cos(PI*convex.getRotation()/ 180.)+0*sin(PI*convex.getRotation()/180.);
}

float Tank::getJ() {
	return j+40*sin(PI*convex.getRotation()/ 180.)-0*cos(PI*convex.getRotation()/180.);
}

float Tank::getAngle() {
	return convex.getRotation();
}

int Tank::getId() const{
	return id;
}

bool Tank::checkCollision(const Bullet& b) const{
	if (id == b.getId())
		return true;
	if (r.getGlobalBounds().intersects(b.getGlobalBounds())
		|| convex.getGlobalBounds().intersects(b.getGlobalBounds()))
		return false;
	return true;
}

Game::Game(sf::Color c1, sf::Color c2) :t1(c1), t2(c2) {
	endMessage.setOutlineColor(sf::Color(0, 0, 0));
	endMessage.setOutlineThickness(6);
}


bool myCheck(const Tank& t, const vector<Bullet>& bullets) {
	for (int i = 0; i < bullets.size(); i++) {
		if (!t.checkCollision(bullets.at(i)))
			return false;
	}
	return true;
}

void Game::checkConditions() {
	if (!myCheck(t1, bullets)) {
		endMessage.setString(" 2nd\nplayer\n Won");
		endMessage.setFillColor(t2.tColor);
		state=2;
	}
	if (!myCheck(t2, bullets)) {
		endMessage.setString(" 1st\nplayer\n Won");
		endMessage.setFillColor(t1.tColor);
		state=2;
	}
}

void Game::run() {
	window.create(sf::VideoMode(500, 500), "Enjoy the Tanks!");
	sf::Font f;
	if (!f.loadFromFile("E:\\2\\SFML_first_Project\\carbontype.ttf")) {}
	endMessage.setCharacterSize(54);
	endMessage.setFont(f);
	sf::Event event;
	while (window.isOpen()) {
		window.clear(sf::Color(255, 255, 255));
		switch (state) {
		case 0:
			t1.display(); t2.display();
			t1.draw(); t2.draw();
			endMessage.setFillColor(t1.tColor);
			endMessage.setString(" 1st\nplayer");
			endMessage.setPosition(10, 100);
			window.draw(endMessage);
			endMessage.setFillColor(t2.tColor);
			endMessage.setString(" 2nd\nplayer");
			endMessage.setPosition(250, 100);
			window.draw(endMessage);
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::KeyPressed)
				{state = 1; t1.random(); t2.random();}
				if (event.type == sf::Event::Closed)
					window.close();
			}
			break;
		case 1:
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed)
					window.close();

				//for First Tank
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
					t1.rotate(-10);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
					t1.rotate(10);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
					t1.setPos(7);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
					t1.setPos(-7);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
					bullets.push_back(Bullet(t1.getI(), t1.getJ(), t1.getAngle(), t1.getId()));

				//for Second Tank
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
					t2.rotate(-10);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
					t2.rotate(10);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
					t2.setPos(7);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
					t2.setPos(-7);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
					bullets.push_back(Bullet(t2.getI(), t2.getJ(), t2.getAngle(), t2.getId()));
			}
			t1.draw(); t2.draw();
			for (int i = 0; i < bullets.size(); i++) {
				try { bullets.at(i).draw(); }
				catch (exception) { bullets.erase(bullets.begin() + i, bullets.begin() + i + 1); }
			}
			checkConditions();
			break;
		case 2:
			endMessage.setPosition(130, 70);
			window.draw(endMessage);
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::KeyPressed || event.type == sf::Event::Closed)
					window.close();
			}
			break;
		}
		window.display();
	}
}
