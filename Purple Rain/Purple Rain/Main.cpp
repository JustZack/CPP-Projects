#include <SFML/Graphics.hpp>
#include <iostream>
#include "Variables.h"
#include "RainDrop.h"
#include <thread>

const int Drop_Count = 2000;
void ResetDrops(RainDrop drops[])
{
	for (int i = 0; i < Drop_Count; i++)
	{
		drops[i].ResetDrop(true);
	}
}
int main()
{
	RainDrop AllDrops[Drop_Count];
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), std::to_string(Drop_Count));
	window.setFramerateLimit(FRAMERATE);
	sf::Event event;

	std::cout << sizeof(AllDrops) << std::endl;

	while (window.isOpen())
	{
		window.clear(sf::Color(216, 191, 216));
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
			{
				ResetDrops(AllDrops);
				continue;
			}
		}

		for (int i = 0; i < Drop_Count; i++)
		{
			if (AllDrops[i].Fall())
			{
				AllDrops[i].ResetDrop(false);
			}
			else
			{
				window.draw(AllDrops[i].Shape);
			}
		}

		window.display();
	}
}