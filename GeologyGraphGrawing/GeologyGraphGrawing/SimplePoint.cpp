#include "SimplePoint.h"

SimplePoint::SimplePoint(sf::Vector2f location)
{
	cartesianCoordinate = location;

	shape.setRadius(1.f);
	shape.setFillColor(sf::Color::Blue);
	shape.setOrigin(sf::Vector2f(shape.getRadius(), shape.getRadius()));
}

void SimplePoint::adjust(sf::Vector2f interval, sf::Vector2f windowSize, sf::Vector2f origin)
{
	shape.setPosition(sf::Vector2f(origin.x + cartesianCoordinate.x * interval.x,
		                           origin.y - cartesianCoordinate.y * interval.y));
}

sf::CircleShape& SimplePoint::getShape()
{
	return shape;
}

sf::Vector2f SimplePoint::getCoordinate()
{
	return cartesianCoordinate;
}

std::string SimplePoint::toString()
{
	return std::string();
}
