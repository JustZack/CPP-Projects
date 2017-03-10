#include <SFML\Graphics.hpp>
#include "World.h"
#include <iostream>


int main()
{
	sf::RenderWindow rw(sf::VideoMode(1000, 1000), "tiles_0.001");
	World w(50, 50, 10.f, rw);
	while (rw.isOpen())
	{
		sf::Event e;
		while (rw.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
			{
				w.close();
				rw.close();
			}
		}

		rw.clear(sf::Color::Cyan);
		w.draw(rw);
		rw.display();
	}
}