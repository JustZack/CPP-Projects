#include <SFML\Graphics.hpp>
#include <fstream>
#include "graph.h"
#include "SimplePoint.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "Window");
	sf::Event event;

	Domain d(-2 * M_PI, 2 * M_PI, -1, 1);
	//14 is the size of the actual paper (7 on either side of an axis)
	Graph g(d, sf::Vector2f(window.getSize().x, window.getSize().y));
	//Pull each token from the line as we go.
	for (float i = -2 * M_PI; i < 2 * M_PI; i += .01)
	{
		g.addPoint(new SimplePoint(sf::Vector2f(i, sin(i))));
		//g.addPoint(new SimplePoint(sf::Vector2f(i, -sin(i))));
		g.addPoint(new SimplePoint(sf::Vector2f(i, cos(i))));
	}

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		if (window.hasFocus())
		{
			//Input goes in here
		}

		window.clear(sf::Color::Black);
		g.draw(window);
		window.display();
	}
	g.~Graph();
}