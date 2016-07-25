#include "RainDrop.h"


void RainDrop::Init(bool FirstTime)
{
	if (FirstTime)
	{
		yspeed = HEIGHT / FRAMERATE;
	}
	else
	{
		yspeed = rand() % (HEIGHT / FRAMERATE) + 5;
	}
	Shape.setPosition(sf::Vector2f(rand() % WIDTH + 0, -yspeed));
	Shape.setSize(sf::Vector2f(5, 15));
	Shape.setFillColor(sf::Color(238, 130, 238));
}
RainDrop::RainDrop()
{
	Init(true);
}
void RainDrop::ResetDrop(bool FirstTime)
{
	if (FirstTime)
	{
		Init(true);
	}
	if (!FirstTime)
	{
		Init(false);
	}
}
bool RainDrop::Fall()
{
	Shape.setPosition(Shape.getPosition().x, Shape.getPosition().y + yspeed);
	if (Shape.getPosition().y > HEIGHT)
	{
		return true;
	}
	return false;
}

