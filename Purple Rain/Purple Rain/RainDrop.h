#pragma once
#include <SFML\Graphics.hpp>
#include "Variables.h"

class RainDrop
{
public:
	float yspeed;
	sf::RectangleShape Shape;

	RainDrop();
	bool Fall();
	void ResetDrop(bool FirstTime);

	void Init(bool FirstTime);
};