#include <E:\2 курс лабки\SFML-2.5.0\include\SFML\Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!");

	// define a circle with radius = 200
	sf::CircleShape circle(200);

	// change the radius to 40
	circle.setRadius(40);

	// change the number of sides (points) to 100
	circle.setPointCount(100);


	// define a triangle
	sf::CircleShape triangle(40, 3);


	// define a square
	sf::CircleShape square(40, 4);

	
	// define an octagon
	sf::CircleShape octagon(40, 8);
	
	//set colors
	circle.setFillColor(sf::Color(10, 20, 250));
	triangle.setFillColor(sf::Color(250, 50, 250));
	square.setFillColor(sf::Color(250, 200, 50));
	octagon.setFillColor(sf::Color(170, 10, 200));


	//set positions
	circle.setPosition(20, 20);
	triangle.setPosition(140, 20);
	square.setPosition(250, 20);
	octagon.setPosition(390, 20);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(circle);
		window.draw(triangle);
		window.draw(square);
		window.draw(octagon);
		window.display();
	}

	return 0;
}

