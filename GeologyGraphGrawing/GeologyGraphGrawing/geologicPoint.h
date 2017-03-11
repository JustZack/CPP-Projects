#pragma once
#include<SFML\Graphics.hpp>
#include <iostream>
#include "PrimitivePoint.h"
class GeologicPoint : public PrimitivePoint
{
private:
	float eyeHeight, tapeDist, rodHeight, evelvation;
	int angle;

	float dist;
	float radsAngle;

	sf::Vector2f polarCoordinate;

public:
	GeologicPoint(float EyeHeight, float TapeDist, float RodHeight, int Angle, float baseElevation);

	// Inherited via PrimitivePoint

	virtual void adjust(sf::Vector2f interval, sf::Vector2f windowSize, sf::Vector2f origin) override;
	virtual sf::CircleShape& getShape() override;
	virtual sf::Vector2f getCoordinate() override;
	virtual std::string toString() override;


};