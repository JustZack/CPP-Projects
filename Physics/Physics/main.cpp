#include <SFML\Graphics.hpp>
#include"World.h"

int main()
{
	//TODO: put the calculations of position on a seperate thread, and refrence the world as a global variable.
	//Create the window, event handler, and limit its framerate
	sf::RenderWindow window(sf::VideoMode(1800, 900), "Window");
	//window.setPosition(sf::Vector2i(-10,0));
	sf::Event event;
	//window.setFramerateLimit(12);

	//Create a world, and do some optionstuff with it first
	World PhysicsWorld(window.getSize().x, window.getSize().y, 10.f, 1);
	PhysicsWorld.RandReset(60);
	//PhysicsWorld.setTrailLength(100000);
	sf::RectangleShape PhysObjShape(sf::Vector2f(10.f,10.f));
	PhysObjShape.setFillColor(sf::Color::White);

	sf::RectangleShape trail(sf::Vector2f(1, 1));
	trail.setFillColor(sf::Color::Blue);

	sf::RectangleShape accelerationShape(sf::Vector2f(1, 1));
	accelerationShape.setFillColor(sf::Color::Red);


	sf::Clock c;
	float keyCooldown = .0f;

	bool pictureTaken = false;
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
				PhysicsWorld.RandReset(60);
			}
			if (keyCooldown > .2f && sf::Keyboard::isKeyPressed(sf::Keyboard::T))
			{
				keyCooldown = .0f;
				if (PhysicsWorld.getdrawTrails())
				{
					PhysicsWorld.hideTrails();
				}
				else if (!PhysicsWorld.getdrawTrails())
				{
					PhysicsWorld.showTrails();
				}
			}
			if (keyCooldown > .2f && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
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
			if (keyCooldown > .2f && sf::Keyboard::isKeyPressed(sf::Keyboard::C))
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
		window.setTitle(PhysicsWorld.getCurrentFrameRate_string() + "   ||   " + std::to_string(PhysicsWorld.getCurrentFrameTime()) + "   ||   " + std::to_string(PhysicsWorld.getRunningtime()));
		
		if(PhysicsWorld.PhysicsObjects.size() > 0)
		{
			//go through each physics object in the world and draw it strail
			if (PhysicsWorld.getdrawTrails())
			{
				for (int i = 0; i < PhysicsWorld.PhysicsObjects.size(); i++)
				{
					for (int j = 0; j < PhysicsWorld.PhysicsObjects.at(i).trail.size(); j++)
					{
						trail.setPosition(PhysicsWorld.PhysicsObjects.at(i).trail.at(j));
						window.draw(trail);
					}
				}				
			}
			//go through each physics object in the world, and draw it
			for (int i = 0; i < PhysicsWorld.PhysicsObjects.size(); i++)
			{
				//Draw each physics object to the window
				PhysObjShape.setPosition(PhysicsWorld.PhysicsObjects.at(i).pos());
				PhysObjShape.setSize(sf::Vector2f(PhysicsWorld.PhysicsObjects.at(i).getWidth(), PhysicsWorld.PhysicsObjects.at(i).getHeight()));
				PhysObjShape.setFillColor(PhysicsWorld.PhysicsObjects.at(i).getColor());
				window.draw(PhysObjShape);
			}
			//go through each physics object ion the world and draw its acceleration magnitude
			if (PhysicsWorld.getdrawAccelerationMagnitude())
			{
				//go through each physics object in the world, and draw their acceleration arrows
				for (int i = 0; i < PhysicsWorld.PhysicsObjects.size(); i++)
				{
					//Draw each physics object to the window
					accelerationShape.setPosition(sf::Vector2f(PhysicsWorld.PhysicsObjects.at(i).pos().x + PhysicsWorld.PhysicsObjects.at(i).getWidth() / 2, PhysicsWorld.PhysicsObjects.at(i).pos().y + PhysicsWorld.PhysicsObjects.at(i).getHeight() / 2));
					accelerationShape.setSize(sf::Vector2f(1.f, PhysicsWorld.PhysicsObjects.at(i).getAccelerationMagnitude()));
					accelerationShape.setRotation(PhysicsWorld.PhysicsObjects.at(i).getAccelerationAngle());
					window.draw(accelerationShape);
				}
			}
		}
		#pragma endregion

		window.display();
	}
}