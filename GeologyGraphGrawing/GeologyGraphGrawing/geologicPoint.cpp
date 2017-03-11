#include "geologicPoint.h"
#define _USE_MATH_DEFINES
#include <math.h>

GeologicPoint::GeologicPoint(float EyeHeight, float TapeDist, float RodHeight, int Angle, float baseElevation)
{
	tapeDist = TapeDist;
	eyeHeight = EyeHeight;
	rodHeight = RodHeight - eyeHeight;
	evelvation = baseElevation - rodHeight;
	if (Angle == 0)
		Angle = 360;
	angle = Angle;

	dist = sqrt(pow(tapeDist, 2) - pow(rodHeight, 2));
	radsAngle = angle * (M_PI / 180.f);

	polarCoordinate = sf::Vector2f(dist, radsAngle);
	cartesianCoordinate = sf::Vector2f(dist * cos(radsAngle), dist * sin(radsAngle));

	shape.setRadius(5.f);
	shape.setFillColor(sf::Color::Color(angle*angle, angle * 2 / 3, angle * 5 / 4, 255));
	shape.setOrigin(sf::Vector2f(shape.getRadius(), shape.getRadius()));
}

sf::Vector2f GeologicPoint::getCoordinate()
{
	return polarCoordinate;
}

sf::CircleShape& GeologicPoint::getShape()
{
	return shape;
}

void GeologicPoint::adjust(sf::Vector2f interval, sf::Vector2f windowSize, sf::Vector2f origin)
{
	//Adjust everything to the interval of the graph
	polarCoordinate - sf::Vector2f(polarCoordinate.x * interval.x, radsAngle);
	cartesianCoordinate = sf::Vector2f((windowSize.x / 2) + cartesianCoordinate.x * interval.x, (windowSize.y / 2) - cartesianCoordinate.y * interval.y);
	shape.setPosition(cartesianCoordinate);
}

std::string GeologicPoint::toString()
{
	std::string toReturn =
		"SHAPE: " + std::to_string(shape.getPosition().x) + ", " + std::to_string(shape.getPosition().y) + "|" +
		"COORDINATES: " + std::to_string(cartesianCoordinate.x) + ", " + std::to_string(cartesianCoordinate.y);
	return toReturn;
}