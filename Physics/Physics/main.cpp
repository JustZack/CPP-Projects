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

	sf::Clock c;
	float keyCooldown = .0f;

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
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			{
				PhysicsWorld.RandReset(10000);
			}
			if (keyCooldown > 1.f && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				keyCooldown = .0f;
				if (PhysicsWorld.getdrawAccelerationMagnitude())
				{
					PhysicsWorld.hideAccelerationMagnitude();
				}
				else if (!PhysicsWorld.getdrawAccelerationMagnitude())
				{
					PhysicsWorld.showAccelerationMagnitude();
				}
			}
			if (keyCooldown > 1.f && sf::Keyboard::isKeyPressed(sf::Keyboard::C))
			{
				keyCooldown = .0f;
				sf::Image screenshot = window.capture();
				screenshot.saveToFile("C:\\Users\\Just_Zack\\Desktop\\App_ScreenShot.png");
			}
		}

		keyCooldown += PhysicsWorld.getCurrentFrameTime();
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