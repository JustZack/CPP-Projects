#pragma once
#include <SFML\Graphics.hpp>
#include "Utilities.h"
class Cell
{
private:
	sf::Vector2f location;
	State state;
public:
	Cell();
	Cell(sf::Vector2f Location);

	State GetState();
	void SetState(State newState);
	
	sf::Vector2f GetLocation();
	void SetLocation(sf::Vector2f newLocation);
};