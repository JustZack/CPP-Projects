#include <SFML\Graphics.hpp>
#include "World.h"

int main()
{
	World d(intPair(1000,1000), 5.f);
	std::cout << sizeof(d)  << std::endl;
	sf::RenderWindow window(sf::VideoMode(640, 360), "Window");
	sf::Event event;
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear();
		window.display();
	}
}