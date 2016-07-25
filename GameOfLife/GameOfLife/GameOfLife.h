#pragma once
#include <SFML\Graphics.hpp>
#include "Utilities.h"
#include "Cell.h"
class GameOfLife
{
private:
	//Sets up each cell in the game
	//First time setup
	void SetupCells();
public:
	float Scale;
	int Generation = 0;
	int LivingThisGen = 0;
	int ArraySize;

	//TODO:
	//Make arrays on HEAP
	//STACK ARRAYS
	std::vector<std::vector<Cell>> VectorCells;
	std::vector<std::vector<Cell>> nextVectorCells;
	//Takes the rows x columns size of the game (NOT PIXEL SIZE)
	//Takes the scalar for the size of the game
	GameOfLife(float Scale, int ArraySize);
	~GameOfLife();
	//Resets all spots on the grid for the game
	void ResetGame();
	//Creates a new game of life
	//Randomly creates minCellCount alive cells on the board
	void Generate(int minCellCount);
	void GenerateGlider(sf::Vector2f StartPoint);
	//Checks for all rules of the game
	void Update();

	float GetScale();
};