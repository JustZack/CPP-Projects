#pragma once
#include <SFML\Graphics.hpp>
#include "Utilities.h"
class Cell
{
private:
	Point location;
	State state;
public:
	//TODO:
	//Instead of having a shape for EVERY cell,
	//Lets make just draw the same shape with different locations and states everytime.

	sf::RectangleShape CellShape;
	Cell();
	Cell(Point Location);

	State GetState();
	void SetState(State newState);
	
	Point GetLocation();
	void SetLocation(Point newLocation);
};