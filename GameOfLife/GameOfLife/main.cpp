#include <SFML\Graphics.hpp>
#include <iostream>
#include "GameOfLife.h"
int main()
{
	//Make the game of life object
	GameOfLife GOL(10, 100);

	sf::RenderWindow GameOfLifeWindow(sf::VideoMode(ARRAY_SIZE * GOL.Scale, GOL.ArraySize * GOL.Scale), "Game of life");
	//Set framerate so i can what is happening
	//GameOfLifeWindow.setFramerateLimit(1);
	
	sf::Event event;
	std::cout << "Cell Size: " << sizeof(Cell) << " Bytes" << std::endl;
	std::cout << "Game Of Life Size: " << sizeof(GameOfLife) << " Bytes" << std::endl;


	if (true)
	{
		for (int y = 0; y < GOL.ArraySize; y += 5)
		{
			for (int x = 3; x < GOL.ArraySize; x += 5)
			{
				//Generate gliders in every 5x5 region of the screen
				GOL.GenerateGlider(sf::Vector2f(x, y));
			}
		}
	}
	else
	{
		//Generate a random grid of live and dead cells
		GOL.Generate(INITIAL_POP);
	}
	//Setup the shape that is used to draw every cell
	sf::RectangleShape CellShape; //New Shape
	CellShape.setOutlineColor(sf::Color(126, 126, 126)); // Setup the color of the outline
	if (GOL.Scale > 2)
	{
		CellShape.setOutlineThickness(1.f); // Setup the thickness of the outline
	}
	CellShape.setSize(sf::Vector2f(GOL.GetScale(), GOL.GetScale())); // Setup the size of the cell
	
	//Clock used to measure Delta Time
	sf::Clock clock;
	float current; //Time of the clock at the current time

	//Update loop
	while (GameOfLifeWindow.isOpen())
	{
		//Check for any events
		while (GameOfLifeWindow.pollEvent(event))
		{
			//Check for the window closing
			if (event.type == sf::Event::Closed)
			{
				GameOfLifeWindow.close();
			}
		}
		//Checks if spacebar was pressed
		while (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			//Do nothing (Acts as pause)
		}
		//Clear window of all pixels and make them white
		GameOfLifeWindow.clear();

		//Draw your stuff here
		for (int x = 0; x < GOL.ArraySize; x++)
		{
			for (int y = 0; y < GOL.ArraySize; y++)
			{
				//Set the positition of the SHAPE to the position of the CELL
				CellShape.setPosition(GOL.VectorCells[x][y].GetLocation());
				//Determine the color of the cell
				if (GOL.VectorCells[x][y].GetState())
				{
					CellShape.setFillColor(sf::Color::White);
				}
				else
				{
					CellShape.setFillColor(sf::Color::Black);
				}
				//Finally, draw the cell onto the window
				GameOfLifeWindow.draw(CellShape);
			}
		}
		//Updates the states of all of the cells
		//GOL.Update();
		//Display the bitmap image
		GameOfLifeWindow.display();
		//FPS mesurement
		current = clock.restart().asSeconds();
		std::cout << " | " << (1.f / current) << " Frames(Generations) per second" << std::endl;
	}
}