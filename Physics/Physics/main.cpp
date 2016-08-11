#include <SFML\Graphics.hpp>
#include"World.h"
#include "Objects.h"

int main()
{
	//Create the window, event handler, and limit its framerate
	sf::RenderWindow window(sf::VideoMode(1800, 900), "Window");
	//window.setPosition(sf::Vector2i(-10,0));
	sf::Event event;

	//Create a world, and do some optionstuff with it first
	World PhysicsWorld(window.getSize().x, window.getSize().y, 10.f, 1.f, 9.81f);

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
		
		//This block updates the locations of all objects in the world
		//and draws them to the screen
		#pragma region Physics World Update and Drawing
		//This updates ALL of the physics involved in the world
		PhysicsWorld.Update();
		PhysicsWorld.Draw(window);
		#pragma endregion

		window.display();
	}
}