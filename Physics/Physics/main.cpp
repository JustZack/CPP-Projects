#include <SFML\Graphics.hpp>
#include"World.h"
#include "Objects.h"

int main()
{
	//Create the window, event handler, and limit its framerate
	sf::RenderWindow window(sf::VideoMode(1800, 900), "Window");
	//window.setPosition(sf::Vector2i(-10,0));
	sf::Event event;
	//window.setFramerateLimit(12);

	//Create a world, and do some optionstuff with it first
	World PhysicsWorld(window.getSize().x, window.getSize().y, 10.f, 1, 9.81f);

	sf::RectangleShape PhysObjShape(sf::Vector2f(10.f,10.f));
	PhysObjShape.setFillColor(sf::Color::White);

	sf::RectangleShape trail(sf::Vector2f(1, 1));
	trail.setFillColor(sf::Color::Blue);

	sf::RectangleShape accelerationShape(sf::Vector2f(1, 1));
	accelerationShape.setFillColor(sf::Color::Red);

	PhysicsWorld.RandReset(100);

	int objcount = 0;

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
				PhysicsWorld.RandReset(100);
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
		window.setTitle(std::to_string(PhysicsWorld.getCurrentFrameRate()) + "   ||   " + std::to_string(PhysicsWorld.getCurrentFrameTime()) + "   ||   " + std::to_string(PhysicsWorld.getRunningtime()));
		
			//go through each physics object in the world, and draw it
			for (int i = 0; i < PhysicsWorld.Objects.size(); i++)
			{
				//Draw each physics object to the window
				PhysObjShape.setPosition(sf::Vector2f(PhysicsWorld.Objects.at(i).x(), PhysicsWorld.Objects.at(i).y()));
				PhysObjShape.setSize(sf::Vector2f(10.f, 10.f));
				PhysObjShape.setFillColor(PhysicsWorld.Objects.at(i).color());
				window.draw(PhysObjShape);
			}
			//go through each physics object ion the world and draw its acceleration magnitude
			if (PhysicsWorld.getdrawAccelerationMagnitude())
			{
				//go through each physics object in the world, and draw their acceleration arrows
				for (int i = 0; i < PhysicsWorld.getObjects().size(); i++)
				{
					//Draw each physics object to the window
					accelerationShape.setPosition(PhysicsWorld.Objects.at(i).posCenter());
					accelerationShape.setSize(sf::Vector2f(1.f, PhysicsWorld.Objects.at(i).accelerationMagnitude()));
					accelerationShape.setRotation(PhysicsWorld.Objects.at(i).accelerationAngle());
					window.draw(accelerationShape);
				}
			}
		
		#pragma endregion

		window.display();
	}
}