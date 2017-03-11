#pragma once
#include <string>
#include <SFML\Graphics.hpp>
#include "smallStructs.h"
#include "PrimitivePoint.h"
/*
	Class for storing mathemtical functions
*/
class Function
{
private:
	/*
		Regex string required to evaluate a function
	*/
	static std::string expressionRegex;
	/*
		The domain of the graph the function is being drawn to.
	*/
	static Domain& graphDomain;
	/*
		The actual unparsed expression.
	*/
	std::string expression;
	/*
		The expression parsed as a ___ notation
		___ = i might decide to do post, pre or infix notation.
	*/
	char* parsedExpression;
	/*
		Boolean determining if we want to draw the function on the graph.
	*/
	bool draw = true;
	/*
		Vector of points refering to every point on the graph (that needs to be drawn)
		This vector is reset, and recalculated, everytime one of these conditions is met
			The window (Domain) changes
			The expression changes
			... more to come?
	*/
	std::vector<PrimitivePoint*> points;
public:
	/*
		Overloaded constructor that takes the expression, 
		as a string, and a refrence to the domain of the graph. 
	*/
	Function(std::string expression, Domain& GraphDomain);

	/*
		Calculate ALL points on the domain for the graph
	*/
	void calculate();

	/*
		Calculate the point at the specified x value
	*/
	PrimitivePoint calculate(float xValue);


};