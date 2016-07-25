//sfml used to sf::RenderWindow.Draw() stuff to the sf::RenderWindow
#include <SFML\Graphics.hpp>
//Set of defined variables used to define
#include "Variables.h"
//Lets us use some more STD:: stuff (like cout)
#include <iostream>
#include <vector>

#include "Tile.h"






//Draw all of our objects
void Draw(sf::RenderWindow &window, std::vector<Tile> ObjectList )
{
	window.clear();
	for each (Tile tile in ObjectList)
	{
		window.draw(tile.TileShape);
	}
	window.display();
}
//Entry point for our application
int main()
{
	//Create the main render window -- this displays our game
	sf::RenderWindow Window(sf::VideoMode(WIDTH, HEIGTH), "Tiles");
	//Window.setFramerateLimit(60);
	sf::Event event;
	while (Window.isOpen())
	{
		while (Window.pollEvent(event))
		{
			std::cout << event.type << std::endl;
			//Check if the event was to close the window
			if (event.type == sf::Event::Closed)
			{
				//Close the application
				Window.close();
			}
		}
	}
}