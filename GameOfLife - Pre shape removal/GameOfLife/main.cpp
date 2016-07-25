#include <SFML\Graphics.hpp>
#include <iostream>
#include "GameOfLife.h"
int main()
{
	sf::RenderWindow GameOfLifeWindow(sf::VideoMode(900,900), "Game of life");
	//GameOfLifeWindow.setFramerateLimit(144);
	sf::Event event;
	std::cout << sizeof(GameOfLife) << std::endl;

	GameOfLife GameOfThatLifeYo(Size(30,30), 30);
	GameOfThatLifeYo.Generate(500);
	while (GameOfLifeWindow.isOpen())
	{
		while (GameOfLifeWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				GameOfLifeWindow.close();
			}
		}

		//Clear window of all pixels and make them white
		GameOfLifeWindow.clear(sf::Color::White);

		//Draw your stuff here
		for (int x = 0; x < GameOfThatLifeYo.GetSize().Width; x++)
		{
			for (int y = 0; y < GameOfThatLifeYo.GetSize().Height; y++)
			{
				
				//std::cout << GameOfThatLifeYo.Cells[x][y].CellShape.getPosition().x << ", " << GameOfThatLifeYo.Cells[x][y].CellShape.getPosition().y << std::endl;
				//std::cout << x << ", " << y << std::endl;
				GameOfLifeWindow.draw(GameOfThatLifeYo.Cells[x][y].CellShape);
			}
		}
		//Updates the states of all of the cells
		GameOfThatLifeYo.Update();
		//Display the bitmap image
		GameOfLifeWindow.display();
	}
	system("PAUSE");
}