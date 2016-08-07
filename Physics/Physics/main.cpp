#include <SFML\Graphics.hpp>
#include"World.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1800, 900), "Window");
	sf::Event event;
	//window.setFramerateLimit(60);

	//Create a world
	World PhysicsWorld(window.getSize().x, window.getSize().y, .75f, 1);
	PhysicsWorld.setDrawTrails(true);
	PhysicsWorld.RandReset(600);

	sf::RectangleShape PhysObjShape(sf::Vector2f(10.f,10.f));
	PhysObjShape.setFillColor(sf::Color::White);

	sf::RectangleShape trail(sf::Vector2f(1, 1));
	trail.setFillColor(sf::Color::Blue);

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
		window.setTitle(PhysicsWorld.getCurrentFrameRate_string());
		if(PhysicsWorld.PhysicsObjects.size() > 0)
		{
		//go through each physics object in the world
			for (int i = 0; i < PhysicsWorld.PhysicsObjects.size(); i++)
			{
				//Go through each objects point on their trail, and draw it.
				//Only works if the drawTrials member is true. Defualts to false;
				if (PhysicsWorld.DrawTrails() == true)
				{
					for (int j = 0; j < PhysicsWorld.PhysicsObjects.at(i).prevPoints.size(); j++)
					{
						trail.setPosition(PhysicsWorld.PhysicsObjects.at(i).prevPoints.at(j));
						window.draw(trail);
					}
				}

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