#pragma once
#include <SFML\Graphics.hpp>
#include "Utilities.h"
#include "Cell.h"
class GameOfLife
{
private:
	float Scale;
	float SeperationScalar = 1.1f;
public:
	int Generation;
	int LivingThisGen;
	int ArraySize;

	//TODO:
	//Make arrays on HEAP
	//STACK ARRAYS
	Cell Cells[ARRAY_SIZE][ARRAY_SIZE];
	Cell nextCells[ARRAY_SIZE][ARRAY_SIZE];
	//Takes the rows x columns size of the game (NOT PIXEL SIZE)
	//Takes the scalar for the size of the game
	GameOfLife(float Scale, int ArraySize);
	~GameOfLife();
	//Resets all spots on the grid for the game
	void ResetGame(bool ResetLocations);
	//Creates a new game of life
	//Randomly creates minCellCount alive cells on the board
	void Generate(int minCellCount);
	void GenerateGlider(sf::Vector2f StartPoint);
	//Checks for all rules of the game
	void Update();

	float GetScale();

	float GetSperationScalar();
};