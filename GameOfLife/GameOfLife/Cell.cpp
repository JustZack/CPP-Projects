#include "Cell.h"

//Defualt constructor (for arrays and stuff man)
Cell::Cell()
{
	SetState(State::Dead);
}
//Main constructor
//Sets the location of the new cell to the location received
//And sets the cells state to dead
Cell::Cell(sf::Vector2f Location)
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
}

//Returns the location of the cell 
//based on pixel location
sf::Vector2f Cell::GetLocation()
{
	return location;
}
//Sets the location of the cell to the received point
//And sets the location of the shape that will be rendered
void Cell::SetLocation(sf::Vector2f newLocation)
{
	location = newLocation;
}