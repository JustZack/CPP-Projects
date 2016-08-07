#include <SFML\Graphics.hpp>
#include"World.h"

int main()
{
	//Create the window, event handler, and limit its framerate
	sf::RenderWindow window(sf::VideoMode(3286, 1080), "Window");
	window.setPosition(sf::Vector2i(-20, 0));
	sf::Event event;
	//window.setFramerateLimit(12);

	//Create a world, and do some optionstuff with it first
	World PhysicsWorld(window.getSize().x, window.getSize().y, 1.f, 1);
	PhysicsWorld.RandReset(60);
	PhysicsWorld.setDrawTrails(true);
	PhysicsWorld.setTrailLength(100000);
	PhysicsWorld.setFrameRateInterval(.5f);

	sf::RectangleShape PhysObjShape(sf::Vector2f(10.f,10.f));
	PhysObjShape.setFillColor(sf::Color::White);

	sf::RectangleShape trail(sf::Vector2f(1, 1));
	trail.setFillColor(sf::Color::Blue);


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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			PhysicsWorld.RandReset(60);

			PhysicsWorld.PlaneReset(10.f);
		}
		if (keyCooldown > .5f && sf::Keyboard::isKeyPressed(sf::Keyboard::T))
		{
			keyCooldown = .0f;
			PhysicsWorld.setDrawTrails(!PhysicsWorld.getDrawTrails());
		}
		if (keyCooldown > .5f && sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		{
			sf::Image screenshot = window.capture();
			screenshot.saveToFile("C:\\Users\\Just_Zack\\Desktop\\App_ScreenShot.png");
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
			//go through each physics object in the world
			for (int i = 0; i < PhysicsWorld.PhysicsObjects.size(); i++)
			{
				//Go through each objects point on their trail, and draw it.
				//Only works if the drawTrials member is true. Defualts to false;
				if (PhysicsWorld.getDrawTrails() == true)
				{
					for (int j = 0; j < PhysicsWorld.PhysicsObjects.at(i).prevPoints.size(); j++)
					{
						trail.setPosition(PhysicsWorld.PhysicsObjects.at(i).prevPoints.at(j));
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
		}
		#pragma endregion

		window.display();
	}
}