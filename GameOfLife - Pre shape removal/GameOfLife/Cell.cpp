#include "Cell.h"

//Defualt constructor (for arrays and stuff man)
Cell::Cell()
{
	SetState(State::Dead);
}
//Main constructor
//Sets the location of the new cell to the location received
//And sets the cells state to dead
Cell::Cell(Point Location)
{
	SetLocation(Location);
	SetState(State::Dead);
}

//Returns the state of the cell (Alive or dead)
State Cell::GetState()
{
	return state;
}
//Sets the state of the cell to the received state
//And Sets the color of the shape that will be rendered
void Cell::SetState(State newState)
{
	state = newState;
	switch (state)
	{
	case Dead:
		CellShape.setFillColor(sf::Color::White);
		break;
	case Alive:
		CellShape.setFillColor(sf::Color::Black);
		break;
	}
}

//Returns the location of the cell 
//based on pixel location
Point Cell::GetLocation()
{
	return location;
}
//Sets the location of the cell to the received point
//And sets the location of the shape that will be rendered
void Cell::SetLocation(Point newLocation)
{
	location = newLocation;
	CellShape.setPosition(sf::Vector2f(location.x, location.y));
}