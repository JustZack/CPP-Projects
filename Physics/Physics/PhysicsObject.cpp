#include "PhysicsObject.h"
#include <iostream>
PhysicsObject::PhysicsObject(float Width, float Height, float X, float Y, float Mass, float Bounciness, float CoefficientOfFriction, sf::Color Color)
{
	width = Width;
	height = Height;
	x = X;
	y = Y;
	mass = Mass;
	bounciness = Bounciness;
	coefficientOfFriction = CoefficientOfFriction;

	color = Color;

	xSpeed = 0;
	ySpeed = 0;
}

void PhysicsObject::Update(float &frameTime)
{
	//Check if the physics object collided with the edges of the world(A.K.A the bounds of the window) 
	EdgeCollisionCheck(frameTime);
	//Check if the objects x velocity is so small that it should just become zero.
	//This keep the objects from having a velocity that is something to the tune of 1px/year. that is a waste of proccessing power.
	if (xSpeed < xSpeed / 1000 && xSpeed > -(xSpeed / 1000))
	{
		xSpeed = 0;
	}

	MathCalculations(frameTime);

	
	PopulateTrails();
}
void PhysicsObject::EdgeCollisionCheck(float &frameTime)
{
	if (x + width >= windowWidth || x <= 0)
	{
		if (x + width >= windowWidth)
		{
			if (xSpeed > 0)
			{
				xSpeed *= -bounciness;
			}
		}
		else if (x <= 0)
		{
			if (xSpeed < 0)
			{
				xSpeed *= -bounciness;
			}
		}
	}
	else
	{

	}
	if (y + height >= windowHeight || y <= 0)
	{
		if (y + height >= windowHeight)
		{
			if (ySpeed > 0)
			{
				ySpeed *= -bounciness;
				xSpeed *= bounciness;
			}
		}
		else if (y <= 0)
		{
			if (ySpeed < 0)
			{
				ySpeed *= -bounciness;
				xSpeed *= bounciness;
			}
		}
	}
	else
	{
		ySpeed += g * frameTime * scale;
	}
}
void PhysicsObject::MathCalculations(float &frameTime)
{
	KE = (.5) * mass * ySpeed * ySpeed;
	PE = mass * g * (windowHeight - (y + height));
	a = abs(sqrt((xSpeed * xSpeed) + (ySpeed * ySpeed)));

	x += (xSpeed * frameTime);
	y += (ySpeed * frameTime);
}
void PhysicsObject::PopulateTrails()
{
	if (drawTrails)
	{
		if (prevPoints.size() > trailLength)
		{
			prevPoints.erase(prevPoints.begin());
		}
		prevPoints.push_back(sf::Vector2f(x + width / 2, y + height / 2));
	}
}

sf::Vector2f PhysicsObject::pos()
{
	return sf::Vector2f(x, y);
}
std::vector<sf::Vector2f> PhysicsObject::getPreviousPoints()
{
	return prevPoints;
}

void PhysicsObject::setXSpeed(float &newXSpeed)
{
	xSpeed = newXSpeed * scale;
}
void PhysicsObject::setYSpeed(float &newYSpeed)
{
	ySpeed = newYSpeed * scale;
}

float PhysicsObject::getHeight()
{
	return height;
}
float PhysicsObject::getWidth()
{
	return width;
}

void PhysicsObject::setColor(sf::Color &Color)
{
	color = Color;
}
sf::Color PhysicsObject::getColor()
{
	return color;
}

void PhysicsObject::setWorldConstants(float Scale, int WindowWidth, int WindowHeight, float Gravity, int TrailLength)
{
	scale = Scale;
	windowWidth = WindowWidth;
	windowHeight = WindowHeight;
	g = Gravity * scale;
	trailLength = TrailLength;

	width *= scale;
	height *= scale;

}

void PhysicsObject::setDrawTrails(bool &DrawTrails)
{
	drawTrails = DrawTrails;
}
bool PhysicsObject::getDrawTrails()
{
	return drawTrails;
}

void PhysicsObject::setTrailLength(int &TrailLength)
{
	trailLength = TrailLength;
}
int PhysicsObject::getTrailLength()
{
	return trailLength;
}

void PhysicsObject::setCollision(bool &Collide)
{
	collision = Collide;
}
bool PhysicsObject::getCollision()
{
	return collision;
}

void PhysicsObject::setCollision(int &CollisionLayer)
{
	collisionLayer = CollisionLayer;
}
int PhysicsObject::getCollisionLayer()
{
	return collisionLayer;
}