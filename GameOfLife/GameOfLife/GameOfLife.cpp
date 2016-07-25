#include "GameOfLife.h"
#include <iostream>

//Constructor
GameOfLife::GameOfLife(float Scale, int ArraySize)
{
	this->Scale = Scale;
	this->ArraySize = ArraySize;

 	//This always goes last because it uses both ArraySize and Scale.
	SetupCells();
}
//Destructor
GameOfLife::~GameOfLife()
{
	//Delete heap arrays here
}
//Set up every cell on the board for the game
void GameOfLife::SetupCells()
{
	
	for (int x = 1; x <= ArraySize; x++)
	{
		std::vector<Cell> Column;
		for (int y = 1; y <= ArraySize; y++)
		{
			Cell temp(sf::Vector2f(x * Scale, y * Scale));
			temp.SetState(State::Dead);
			Column.assign(y, temp);
			//std::cout << Column.at(y).GetLocation().y;
			//std::cout << Column.at(y).GetLocation().x << " , " << Column.at(y).GetLocation().y << std::endl;

		}
		VectorCells.assign(x, Column);
	}

	for (int x = 0; x < ArraySize; x++)
	{
		for (int y = 0; y < ArraySize; y++)
		{
			std::cout << VectorCells[x][y].GetLocation().x <<  " , " << VectorCells[x][y].GetLocation().y << std::endl;
		}
	}

	nextVectorCells = VectorCells;
}
//Reset every cell on the board
//DEPRECIATED?
void GameOfLife::ResetGame()
{
	Generation = 0;
	LivingThisGen = 0;
	for (int x = 0; x < ArraySize; x++)
	{
		for (int y = 0; y < ArraySize; y++)
		{
		}
	}
}
//Generates a random grid of living or dead cells
void GameOfLife::Generate(int minCellCount)
{
	int tempx, tempy, CurrentCellCount = 0;
	while (CurrentCellCount < minCellCount)
	{
		tempx = rand() % ArraySize + 0;
		tempy = rand() % ArraySize + 0;
		if (VectorCells[tempx][tempy].GetState())
		{
			//Do nothing because a cell was already made here
		}
		else
		{
			VectorCells[tempx][tempy].SetState(State::Alive);
			CurrentCellCount++;
		}
	}
	std::cout << "Generation of " << CurrentCellCount << " cells finished" << std::endl;
}
//Generates one glider starting at the specified position
void GameOfLife::GenerateGlider(sf::Vector2f StartPoint)
{
	int StartPointx = StartPoint.x;
	int StartPointy = StartPoint.y;
	VectorCells[StartPointx - 2][StartPointy + 0].SetState(State::Alive);
	VectorCells[StartPointx - 2][StartPointy + 1].SetState(State::Alive);
	VectorCells[StartPointx - 0][StartPointy + 1].SetState(State::Alive);
	VectorCells[StartPointx - 2][StartPointy + 2].SetState(State::Alive);
	VectorCells[StartPointx - 1][StartPointy + 2].SetState(State::Alive);
}
//Update each cell to its new state
void GameOfLife::Update()
{
	int neighbors = 0;
	int Tempx, Tempy;
	//Makes the next cells array equal to the cells array
	//DEPRECIATED?
	/*for (int x = 0; x < ARRAY_SIZE; x++)
	{
		for (int y = 0; y < ARRAY_SIZE; y++)
		{
			nextCells[x][y].SetState(Cells[x][y].GetState());
		}
	}*/
	for (int x = 0; x < ArraySize; x++)
	{
		for (int y = 0; y < ArraySize; y++)
		{
			//Check all 8 neighbors of each cell
			for (int Rows = -1; Rows <= 1; Rows++)
			{
				for (int Columns = -1; Columns <= 1; Columns++)
				{
					//Check if any of the neighbors are out of bounds of the array
					//And do a warp around mechanic if they are.
					//Check if too far right or left
					if (x + Rows == -1)
					{
						Tempx = ArraySize - 1;
					}
					else if (x + Rows >= ArraySize)
					{
						Tempx = 0;
					}
					else
					{
						Tempx = x + Rows;
					}
					//Check if too far up or down
					if (y + Columns == -1)
					{
						Tempy = ArraySize - 1;
					}
					else if (y + Columns >= ArraySize)
					{
						Tempy = 0;
					}
					else
					{
						Tempy = y + Columns;
					}

					//Add to the neighbors counter
					neighbors += VectorCells[Tempx][Tempy].GetState();
				}
			}
			//Removes the current cells self from the equation
			neighbors -= VectorCells[x][y].GetState();
			//Checks for rules of life
			if ((VectorCells[x][y].GetState() == 1) && (neighbors <  2))      nextVectorCells[x][y].SetState(State::Dead);			 //Lonley
			else if ((VectorCells[x][y].GetState() == 1) && (neighbors >  3)) nextVectorCells[x][y].SetState(State::Dead);			 //Overpopulation
			else if ((VectorCells[x][y].GetState() == 0) && (neighbors == 3)) nextVectorCells[x][y].SetState(State::Alive);          //Reproduction
			else														nextVectorCells[x][y].SetState(VectorCells[x][y].GetState());//Stasis
			neighbors = 0;
		}
	}
	//Make the new board equal to the board that we display
	for (int x = 0; x < ArraySize; x++)
	{
		for (int y = 0; y < ArraySize; y++)
		{
			VectorCells[x][y].SetState(nextVectorCells[x][y].GetState());
			if (VectorCells[x][y].GetState() == 1)
			{
				LivingThisGen++;
			}
		}
	}
	Generation++;
	std::cout << "Gen: " << Generation << " | Pop: " << LivingThisGen;
	LivingThisGen = 0;
}
//Get the scale of the world
float GameOfLife::GetScale()
{
	return Scale;
}