#include <SFML\Graphics.hpp>
#include <iostream>
#include "GameOfLife.h"
int main()
{
	//Make the game of life object
	GameOfLife GOL(10, ARRAY_SIZE);

	sf::Color colors[3] = { sf::Color::Black , sf::Color::White , sf::Color::Red};

	sf::RenderWindow GameOfLifeWindow(sf::VideoMode(GOL.ArraySize * GOL.GetScale() * GOL.GetSperationScalar(), GOL.ArraySize * GOL.GetScale() * GOL.GetSperationScalar()), "Game of life");
	
	sf::Event event;

	std::cout << "Cell Size: " << sizeof(Cell) << " Bytes" << std::endl;
	std::cout << "Game Of Life Size: " << sizeof(GameOfLife) << " Bytes" << std::endl;

	//Generate gliders OR generate a random assortment of cells
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
	else if(false)
	{
		//Generate a random grid of live and dead cells
		GOL.Generate(INITIAL_POP);
	}

	//Setup the shape that is used to draw every cell
	sf::RectangleShape CellShape; //New Shape
	CellShape.setOutlineColor(sf::Color(126, 126, 126)); // Setup the color of the outline
	if (GOL.GetScale() > 2)
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
		//Makes sure the space bar specificaly is not pressed.
		//This is called "Play Mode"
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			//Clear window of all pixels and make them white
			GameOfLifeWindow.clear();

			//Draw your stuff here
			for (int x = 0; x < GOL.ArraySize; x++)
			{
				for (int y = 0; y < GOL.ArraySize; y++)
				{
					//Set the positition of the SHAPE to the position of the CELL
					CellShape.setPosition(GOL.Cells[x][y].GetLocation());
					//Determine the color of the cell
					if (GOL.Cells[x][y].GetState())
					{
						CellShape.setFillColor(colors[1]);
					}
					else
					{
						CellShape.setFillColor(colors[0]);
					}

					//Finally, draw the cell onto the window
					//Costs us about 30 FPS
					GameOfLifeWindow.draw(CellShape);
				}
			}
			//Updates all of the cells
			GOL.Update();
		}
		//If the spacebar is pressed
		//This activates "Edit Mode"
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			//Make sure the mouse is even in the bounds of the window
			if (sf::Mouse::getPosition(GameOfLifeWindow).x >= 0 && sf::Mouse::getPosition(GameOfLifeWindow).x < GameOfLifeWindow.getSize().x && sf::Mouse::getPosition(GameOfLifeWindow).y >= 0 && sf::Mouse::getPosition(GameOfLifeWindow).y < GameOfLifeWindow.getSize().y)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Right) || sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Mouse::isButtonPressed(sf::Mouse::Right))
				{
					float x = sf::Mouse::getPosition(GameOfLifeWindow).x / (GOL.GetScale() * GOL.GetSperationScalar());
					float y = sf::Mouse::getPosition(GameOfLifeWindow).y / (GOL.GetScale() * GOL.GetSperationScalar());
					int X = floorf(x);
					int Y = floorf(y);
					CellShape.setPosition(GOL.Cells[X][Y].GetLocation());
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{

						GOL.Cells[X][Y].SetState(State::Alive);
						CellShape.setFillColor(colors[1]);
						//GameOfLifeWindow.draw(CellShape);
					}
					else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
					{
						GOL.Cells[X][Y].SetState(State::Dead);
						CellShape.setFillColor(colors[0]);
					}
					GameOfLifeWindow.draw(CellShape);
				}
				
			}
		}
		//Used to clear the board at anytime
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
			{
				//Reset all of the cells
				GOL.ResetGame(false);
				//Draw your stuff here
				for (int x = 0; x < GOL.ArraySize; x++)
				{
					for (int y = 0; y < GOL.ArraySize; y++)
					{
						//Set the positition of the SHAPE to the position of the CELL
						CellShape.setPosition(GOL.Cells[x][y].GetLocation());
						//Determine the color of the cell
						if (GOL.Cells[x][y].GetState())
						{
							CellShape.setFillColor(colors[1]);
						}
						else
						{
							CellShape.setFillColor(colors[0]);
						}

						//Finally, draw the cell onto the window
						//Costs us about 30 FPS
						GameOfLifeWindow.draw(CellShape);
					}
				}
			}
		//FPS mesurement
		current = clock.restart().asSeconds();
		std::cout << " | " << (1.f / current) << " Frames(Generations) per second" << std::endl;
		//Display the bitmap image
		GameOfLifeWindow.display();
	}
}