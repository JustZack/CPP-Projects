#include "GameOfLife.h"
#include <iostream>

GameOfLife::GameOfLife(Size Size, float Scale)
{
	size = Size;
	SetupCells(Scale);
}

void GameOfLife::SetupCells(float Scale)
{
	for (int x = 0; x < size.Width; x++)
	{
		for (int y = 0; y < size.Height; y++)
		{
			Cells[x][y].SetLocation(Point(x * Scale, y * Scale));
			Cells[x][y].CellShape.setSize(sf::Vector2f(Scale,Scale));
			//std::cout << Cells[x][y].CellShape.getPosition().x << ", " << Cells[x][y].CellShape.getPosition().y << std::endl;
			//std::cout << Cells[x][y].GetState() << std::endl;
		}
	}
}

//Generates a random grid of living or dead cells
void GameOfLife::Generate(int minCellCount)
{
	int CurrentCellCount = 0;
	int tempx, tempy;
	while (CurrentCellCount < minCellCount)
	{
		tempx = rand() % size.Width + 0;
		tempy = rand() % size.Height + 0;
		if (Cells[tempx][tempy].GetState() == State::Alive)
		{
			//Do nothing because a cell was already made here
		}
		else
		{
			Cells[tempx][tempy].SetState(State::Alive);
			CurrentCellCount++;
		}
	}
}

//Update each cell to its new state
void GameOfLife::Update()
{
	int LivingThisGen = 0;
	Cell nextCells[30][30];
	for (int x = 0; x < size.Width; x++)
	{
		for (int y = 0; y < size.Height; y++)
		{
			nextCells[x][y].SetState(Cells[x][y].GetState());
		}
	}
	int neighbors = 0;
	for (int x = 0; x < size.Width - 1; x++)
	{
		for (int y = 0; y < size.Height- 1; y++)
		{
			//Check each and every neighbor of this cell
			for (int Rows = -1; Rows <= 1; Rows++)
			{
				for (int Columns = -1; Columns <= 1; Columns++)
				{
					//makes sure we cant get an index out of bounds exception
					if (x + Rows > -1 || x + Rows < 30 - 1)
					{
						if (y + Columns > -1 || y + Columns < 30 - 1)
						{
							//Add to the neighbors interger variable
							//Can add zero or one depending on alive or dead
							neighbors += Cells[x + Rows][y + Columns].GetState();
						}
					}
				}
			}
			//Removes the current cells self from the equation
			neighbors -= Cells[x][y].GetState();
			//Checks for rules of life
			if ((Cells[x][y].GetState() == 1) && (neighbors <  2))      nextCells[x][y].SetState(State::Dead);			 //Lonley
			else if ((Cells[x][y].GetState() == 1) && (neighbors >  3)) nextCells[x][y].SetState(State::Dead);			 //Overpopulation
			else if ((Cells[x][y].GetState() == 0) && (neighbors == 3)) nextCells[x][y].SetState(State::Alive);          //Reproduction
			else														nextCells[x][y].SetState(Cells[x][y].GetState());//Stasis
			neighbors = 0;
		}
	}
	for (int x = 0; x < size.Width - 1; x++)
	{
		for (int y = 0; y < size.Height - 1; y++)
		{
			Cells[x][y].SetState(nextCells[x][y].GetState());
			if (Cells[x][y].GetState() == 1)
			{
				LivingThisGen++;
			}
		}
	}
	Generation++;
	//std::cout << "Gen: " << Generation << " | Amount Alive: " << LivingThisGen << std::endl;
}
//Returns a size object containing the size in rows x columns of the game
Size GameOfLife::GetSize()
{
	return size;
}