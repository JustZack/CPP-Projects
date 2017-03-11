#pragma once
#include <SFML\Graphics.hpp>

/*
	Basic parent class for a point. 
	This classes methods MUST be implemented for the graph to read your points!
*/
class PrimitivePoint
{
public:
	//The x and y coordinates that are used on the graph
	sf::Vector2f cartesianCoordinate;
	//The shape used to draw the point
	sf::CircleShape shape;

	/*
		Adjusts the points to work on the graph.
		Should be called when the point is added to the graph
	*/ 
	virtual void adjust(sf::Vector2f interval, sf::Vector2f windowSize, sf::Vector2f origin) = 0;

	/*
		Returns the shape for this point
		Should be called when you are ready to draw the point
	*/
	virtual sf::CircleShape& getShape() = 0;

	/*
		Returns the corrdinate values of the point you inputed.
		This is NOT the point on the graph, or adjusted coordinates
		This is the base location of the point.
	*/
	virtual sf::Vector2f getCoordinate() = 0;

	/*
		Prints out the objects data
		Could later be used for creating tables of data.
	*/
	virtual std::string toString() = 0;
};