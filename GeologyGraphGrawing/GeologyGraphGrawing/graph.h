#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include "PrimitivePoint.h"
#include "smallStructs.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdexcept>
class Graph
{
private:
	/* MEMBER VAIRBALES */
	/*
		The domain used to determine the window for the graph
	*/
	Domain graphDomain;
	/*
		The origin point for the graph, represented as pixel coordinates
	*/
	sf::Vector2f originPoint;
	/*
		The (pixel) distance between each line on the graph
		The first element refers to the x axis
		The second element refers to the y axis
	*/
	sf::Vector2f pixelInterval;
	/*
		The cartensian distance between the interval lines on the graph
		The first element refers to the x axis spacing
		The second element refers to the y axis spacing
	*/
	sf::Vector2f lineInterval;
	/*
		This is the number of lines the graph should have
		The first element refers to the x axis
		The second element refers to the y axis
	*/
	sf::Vector2f intervalCount;
	/*
		The pixel width AND height of the drawing area.
	*/
	sf::Vector2f windowSize;
	/*
		The pixel location of the center of the drawing surface
	*/
	sf::Vector2f center;
	/*
		All of the lines for the grid
	*/
	std::vector<sf::RectangleShape> lines;
	/*
		The origin axis lines
		0 = x axis
		1 = y axis
	*/
	sf::RectangleShape axisOriginLines[2];
	/*
		The color of the horizontal and vertical lines
		This color is uneditable currently.
	*/
	sf::Color lineColor = sf::Color::White;
	/*
		The color of the lines denoting the center of the graph (origin)
		Thiis color is unediable currently.
	*/
	sf::Color axisLineColor = sf::Color::Red;
	/*
		The width of the interval and axis lines on the graph
	*/
	float lineSize = 2;
	/*
		Vector storing a pointer to every point on the graph
		For a point to be in here, it must be a child of the 
		    PrimativePoint class and implement its methods
	*/
	std::vector<PrimitivePoint*> Points;

	/* FUNCTIONS */
	/*
		Creates all of the 'line' shapes and throws them into the vectors
	*/
	void setup();
	/*
		Checks that the shape in the parameter is within the pixel range of the window
		Overload using rectangle shape
	*/
	bool ensureRange(sf::RectangleShape shape);
	/*
		Checks that the shape in the parameter is within the pixel range of the window
		Overload using circle shape
	*/
	bool ensureRange(sf::CircleShape shape);
public:
	/*
		Overloaded constructor
		Takes a Domain object, which stores the x and y mins and max's for the window.
		Takes the window size, as a vector
	*/
	Graph(Domain GraphDomain, sf::Vector2f WindowSize);

	/*
		Destructor for the Graph
	*/
	~Graph();

	/*
		Draws the graph onto the screen
	*/
	void draw(sf::RenderWindow& rw);

	/*
		Adds a new geolgic point to the graph.
	*/
	void addPoint(PrimitivePoint *p);

	/*
		Set the spacing between the graphs interval lines
	*/
	void setLineInterval(sf::Vector2f newLineInterval);

	/*
		Set the domain of the graph
	*/
	void setDomain(Domain newDomain);
};