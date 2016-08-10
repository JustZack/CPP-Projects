#include "PhysicsObject.h"
#define _USE_MATH_DEFINES 
#include <math.h>
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
	temptrailInterval = trailInterval;
}

void PhysicsObject::Update(float &frameTime)
{
	//Check if the objects x velocity is so small that it should just become zero.
	//This keep the objects from having a velocity that is something to the tune of 1px/year. that is a waste of proccessing power.
	/*if (xSpeed < xSpeed / 1000 && xSpeed > -(xSpeed / 1000))
	{
		xSpeed = 0;
	}
	*/

	//Check if the physics object collided with the edges of the world(A.K.A the bounds of the window) 
	WindowEdgeCollisionCheck(frameTime);

	//Do some math.
	//Get new x and y pos
	//Get acceleration vector
	//Get acceleration angle
	//and much more!
	MathCalculations(frameTime);

	//Add previous positions to the trail vector every interval seconds.
	PopulateTrail(frameTime);
}
void PhysicsObject::WindowEdgeCollisionCheck(float &frameTime)
{
	if (x + width >= windowWidth || x <= 0)
	{
		if (x + width >= windowWidth)
		{
			if (xSpeed > 0)
			{
				xSpeed *= -bounciness;
				ySpeed *= bounciness;
			}
		}
		else if (x <= 0)
		{
			if (xSpeed < 0)
			{
				xSpeed *= -bounciness;
				ySpeed *= bounciness;
			}
		}
	}
	if (y + height >= windowHeight || y <= 0)
	{
		if (y + height >= windowHeight)
		{
			y = windowHeight - height;
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
}
void PhysicsObject::MathCalculations(float &frameTime)
{
	KE = (.5) * mass * ySpeed * ySpeed;
	PE = mass * g * (windowHeight - (y + height));
	if (drawAccelerationMagnitude)
	{
		//Object is mocing straight down or up.
		if (abs(xSpeed) == 0 && abs(ySpeed) > 0)
		{
			acceleration = ySpeed;
			//Object is moving down
			if (ySpeed > 0)
			{
				accelerationAngle = 0.f;
			}
			//Object is moving up
			else if (ySpeed < 0)
			{
				accelerationAngle = 0.f;
			}

		}
		//Object is moving straight left or right.
		else if (abs(ySpeed) == 0 && abs(xSpeed) > 0)
		{
			acceleration = xSpeed;
			//Object is moving right
			if (xSpeed > 0)
			{
				std::cout << "kek" << std::endl;
				accelerationAngle = 270.f;
			}
			//Object is moving left
			else if (xSpeed < 0)
			{
				accelerationAngle = 270.f;
			}
		}
		//Object is not moving at all.
		else if (abs(ySpeed) == 0 && abs(xSpeed) == 0)
		{
			acceleration = 0.f;
			accelerationAngle = 0.f;
		}
		//Object is moving in both directions
		else if (abs(ySpeed) > 0 && abs(xSpeed) > 0)
		{
			//Calculate the acceleration magnitude as a vector (hypotonuse) of the x and y speed.
			acceleration = abs(sqrt((xSpeed * xSpeed) + (ySpeed * ySpeed)));
			//Calculate the acceleration angle from the the triangle that is formed by the x and y speed.
			accelerationAngle = (atan2(ySpeed, xSpeed) * 180 / M_PI);
			if (xSpeed > 0 && -ySpeed > 0)
			{
				//First quadrant
				accelerationAngle -= 90;
			}
			if (xSpeed < 0 && -ySpeed > 0)
			{
				//Second Quadrant
				accelerationAngle += 270;
			}
			if (xSpeed < 0 && -ySpeed < 0)
			{
				//Third Quadrant
				accelerationAngle += 270;
			}
			if (xSpeed > 0 && -ySpeed < 0)
			{
				//Fourth Quadrant
				accelerationAngle += 270;
			}
		}
	}
	x += (xSpeed * frameTime);
	y += ((ySpeed += g * frameTime) * frameTime);
}
void PhysicsObject::PopulateTrail(float &frameTime)
{
	temptrailInterval -= frameTime;
	if (temptrailInterval <= 0.f)
	{
		temptrailInterval = trailInterval;
		if (trail.size() > trailLength)
		{
			trail.erase(trail.begin());
		}
		trail.push_back(sf::Vector2f(x + width / 2, y + height / 2));
	}
}

sf::Vector2f PhysicsObject::pos()
{
	return sf::Vector2f(x, y);
}
std::vector<sf::Vector2f> PhysicsObject::getPreviousPoints()
{
	return trail;
}

void PhysicsObject::setXSpeed(float &newXSpeed)
{
	xSpeed = newXSpeed * scale;
}
float PhysicsObject::getXSpeed()
{
	return xSpeed;
}

void PhysicsObject::setYSpeed(float &newYSpeed)
{
	ySpeed = newYSpeed * scale;
}
float PhysicsObject::getYSpeed()
{
	return ySpeed;
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

void PhysicsObject::setTrailInterval(float &interval)
{
	trailInterval = interval;
}
void PhysicsObject::clearTrails()
{
	trail.clear();
}
void PhysicsObject::showTrails()
{
	drawTrails = true;
}
void PhysicsObject::hideTrails()
{
	drawTrails = false;
}
bool PhysicsObject::getdrawTrails()
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

void PhysicsObject::setCollisionLayer(int &CollisionLayer)
{
	collisionLayer = CollisionLayer;
}
int PhysicsObject::getCollisionLayer()
{
	return collisionLayer;
}

float PhysicsObject::getAccelerationAngle()
{
	return accelerationAngle;
}
float PhysicsObject::getAccelerationMagnitude()
{
	return acceleration;
}

void PhysicsObject::showAccelerationMagnitude()
{
	drawAccelerationMagnitude = true;
}
void PhysicsObject::hideAccelerationMagnitude()
{
	drawAccelerationMagnitude = false;
}
bool PhysicsObject::getdrawAccelerationMagnitude()
{
	return drawAccelerationMagnitude;
}

