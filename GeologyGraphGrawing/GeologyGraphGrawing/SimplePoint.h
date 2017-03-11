#pragma once
#include "PrimitivePoint.h"
class SimplePoint : public PrimitivePoint
{
private:

public:
	SimplePoint(sf::Vector2f location);

	// Inherited via PrimitivePoint

	virtual void adjust(sf::Vector2f interval, sf::Vector2f windowSize, sf::Vector2f origin) override;
	virtual sf::CircleShape& getShape() override;
	virtual sf::Vector2f getCoordinate() override;
	virtual std::string toString() override;
};