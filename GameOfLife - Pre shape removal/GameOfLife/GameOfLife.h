#pragma once
#include <SFML\Graphics.hpp>
#include "Utilities.h"
#include "Cell.h"
class GameOfLife
{
private:
	//Stores size of game privately
	Size size;
	//Sets up each cell in the game
	//First time setup
	void SetupCells(float Scale);
public:
	int Generation = 0;
	Cell Cells[30][30];
	//Takes the rows x columns size of the game (NOT PIXEL SIZE)
	//Takes the scalar for the size of the game
	GameOfLife(Size Size, float Scale);

	//Creates a new game of life
	//Randomises
	void Generate(int minCellCount);
	//Checks for all rules of the game
	void Update();

	Size GetSize();
};