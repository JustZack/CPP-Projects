#include "Object.h"
#define _USE_MATH_DEFINES 
#include <math.h>
#include <iostream>

//TODO: put the calculations of position on a seperate thread that is created when the object is created.

void Object::Init(float &X, float &Y, float &Mass, float &Width, float &Height)
{
	setPosition(X, Y);
	setMass(Mass);
	setDimensions(Width, Height);
	
	float f = .0f;
	setXSpeed(f);
	setYSpeed(f);

	f = .5f;
	setbounciness(f);
	setcoefficientOfFriction(f);

	settrailTimeInterval(f - .25f);

	m_shape.setSize(size());
	m_shape.setPosition(pos());
	m_shape.setFillColor(color());

	m_accelerationShape.setFillColor(sf::Color::Red);
}
Object::Object()
{
	float f = 10.f;
	Init(f, f, f, f, f);
}
Object::Object(float X, float Y, float Mass, float Width, float Height)
{
	Init(X, Y, Mass, Width, Height);
}

void Object::Update(float &frameTime, float &g)
{
	Update_Position(frameTime, g);
	Update_Acceleration();
	Update_PopulateTrail(frameTime);
	WindowEdgeCollisionCheck();
}
void Object::Update_Position(float &frameTime, float &g)
{
	//Check if the object is affected by gravity...
	if (!isAffectedByGravity())
	{
		//Do not change the value of ySpeed because gravity does not act on this object.
	}
	else
	{
		//It is affected by gravity so make gravity act on it.
		ySpeed() += g * frameTime;
	}
	//Save temp x and y values to send to the setPosition() method after wards.
	//Required because this method takes everything by refrence.
	x() += (xSpeed() * frameTime);
	y() += (ySpeed() * frameTime);
	if (isOnScreen())
	{
		m_shape.setPosition(pos());
	}
}
void Object::Update_Acceleration()
{
	//Object is moving straight down or up.
	if (abs(xSpeed()) == 0 && abs(ySpeed()) > 0)
	{
		accelerationMagnitude() = ySpeed();
		//Object is moving down
		if (ySpeed() > 0)
		{
			accelerationAngle() = 0.f;
		}
		//Object is moving up
		else if (ySpeed() < 0)
		{
			accelerationAngle() = 0.f;
		}

	}
	//Object is moving straight left or right.
	else if (abs(ySpeed()) == 0 && abs(xSpeed()) > 0)
	{
		accelerationMagnitude() = xSpeed();
		//Object is moving right
		if (xSpeed() > 0)
		{
			accelerationMagnitude() = 270.f;
		}
		//Object is moving right
		else if (xSpeed() < 0)
		{
			accelerationMagnitude() = 270.f;
		}
	}
	//Object is not moving at all.
	else if (abs(ySpeed()) == 0 && abs(xSpeed()) == 0)
	{
		accelerationMagnitude() = 0.f;
		accelerationAngle() = 0.f;
	}
	//Object is moving in both directions
	else if (abs(ySpeed()) > 0 && abs(xSpeed()) > 0)
	{
		//Calculate the acceleration magnitude as a vector (hypotonuse) of the x and y speed.
		accelerationMagnitude() = abs(sqrt((xSpeed() * xSpeed()) + (ySpeed() * ySpeed())));
		//Calculate the acceleration angle from the the triangle that is formed by the x and y speed.
		accelerationAngle() = (atan2(ySpeed(), xSpeed()) * 180 / M_PI);
		if (xSpeed() > 0 && -ySpeed() > 0)
		{
			//First quadrant
			accelerationAngle() -= 90;
		}
		if (xSpeed() < 0 && -ySpeed() > 0)
		{
			//Second Quadrant
			accelerationAngle() += 270;
		}
		if (xSpeed() < 0 && -ySpeed() < 0)
		{
			//Third Quadrant
			accelerationAngle() += 270;
		}
		if (xSpeed() > 0 && -ySpeed() < 0)
		{
			//Fourth Quadrant
			accelerationAngle() += 270;
		}
	}
	if (isOnScreen())
	{
		if (accelerationMagnitude() == 0)
		{
			showacceleration(false);
		}
		//if (showacceleration())
		{
			accelerationShape().setSize(sf::Vector2f(1.f, accelerationMagnitude()));
			accelerationShape().setRotation(accelerationAngle());
			accelerationShape().setPosition(posCenter());
		}
	}
}
void Object::Update_PopulateTrail(float &frameTime)
{
	m_tempTime_trial += frameTime;
	if (m_tempTime_trial >= m_trailTimeInterval)
	{
		m_tempTime_trial = 0.f;
		m_trail.push_back(posCenter());
	}
}
void Object::WindowEdgeCollisionCheck()
{
	if (x() + width() >= 1920 || x() <= 0)
	{
		if (x() + width() >= 1920)
		{
			if (xSpeed() > 0)
			{
				xSpeed() *= -bounciness();
				ySpeed() *= bounciness();
			}
		}
		else if (x() <= 0)
		{
			if (xSpeed() < 0)
			{
				xSpeed() *= -bounciness();
				ySpeed() *= bounciness();
			}
		}
	}
	if (y() + height() >= 1080 || y() <= 0)
	{
		if (y() + height() >= 1080)
		{
			y() = 1080 - height();
			if (ySpeed() > 0)
			{
				ySpeed() *= -bounciness();
				xSpeed() *= bounciness();
			}
		}
		else if (y() <= 0)
		{
			if (ySpeed() < 0)
			{
				ySpeed() *= -bounciness();
				xSpeed() *= bounciness();
			}
		}
	}
}

void Object::setPosition(float X, float Y)
{
	x() = X;
	y() = Y;
	m_shape.setPosition(pos());
}
sf::Vector2f Object::pos()
{
	return sf::Vector2f(x(), y());
}
float &Object::x()
{
	return m_x;
}
float &Object::y()
{
	return m_y;
}

void Object::setMass(float Mass)
{
	mass() = Mass;
}
float &Object::mass()
{
	return m_mass;
}

void Object::setDimensions(float Width, float Height)
{
	width() = Width;
	height() = Height;
	m_shape.setSize(sf::Vector2f(width(), height()));
	radius() = sqrt(((height() / 2) * (height() / 2)) + ((width() / 2) + (width() / 2)));
	
}
sf::Vector2f Object::size()
{
	return sf::Vector2f(width(), height());
}
sf::Vector2f Object::posCenter()
{
	return sf::Vector2f(x() + (width() / 2), y() + (height() / 2));
}
float &Object::width()
{
	return m_width;
}
float &Object::height()
{
	return m_height;
}

float &Object::radius()
{
	return m_radius;
}

void Object::setXSpeed(float XSpeed)
{
	xSpeed() = XSpeed;
}
float &Object::xSpeed()
{
	return m_xSpeed;
}
void Object::setYSpeed(float YSpeed)
{
	ySpeed() = YSpeed;
}
float &Object::ySpeed()
{
	return m_ySpeed;
}

std::string &Object::name()
{
	return m_name;
}

float &Object::accelerationMagnitude()
{
	return m_accelerationMagnitude;
}
float &Object::accelerationAngle()
{
	return m_accelerationAngle;
}
void Object::showacceleration(bool ShowAcceleration)
{
	showacceleration() = ShowAcceleration;
}
bool &Object::showacceleration()
{
	return m_showacceleration;
}

void Object::setbounciness(float Bounciness)
{
	bounciness() = Bounciness;
}
float &Object::bounciness()
{
	return m_bounciness;
}

void Object::setcoefficientOfFriction(float CoefficientOfFriction)
{
	coefficientOfFriction() = CoefficientOfFriction;
}
float &Object::coefficientOfFriction()
{
	return m_coefficientOfFriction;
}

void Object::isAffectedByGravity(bool AffectedByGravity)
{
	isAffectedByGravity() = AffectedByGravity;
}
bool &Object::isAffectedByGravity()
{
	return m_isAffectedByGravity;
}

void Object::isMoveable(bool Moveable)
{
	isMoveable() = Moveable;
}
bool &Object::isMoveable()
{
	return m_isMoveable;
}

void Object::isOnScreen(bool OnScreen)
{
	isOnScreen() = OnScreen;
	if (isOnScreen())
	{

	}
}
bool &Object::isOnScreen()
{
	return m_isOnScreen;
}

void Object::hasCollision(bool Collides)
{
	hasCollision() = Collides;
}
bool &Object::hasCollision()
{
	return m_hasCollision;
}

void Object::setCollisionLayer(int CollisionLayer)
{
	collisionLayer() = CollisionLayer;
}
int &Object::collisionLayer()
{
	return m_collisionLayer;
}

std::vector<sf::Vector2f> Object::gettrail()
{
	return m_trail;
}
void Object::settrailTimeInterval(float TimeInterval)
{
	m_trailTimeInterval = TimeInterval;
}
float &Object::trailTimeInterval()
{
	return m_trailTimeInterval;
}
void Object::setColor(sf::Color Color)
{
	color() = Color;
	m_shape.setFillColor(color());
}
sf::Color &Object::color()
{
	return m_color;
}

void Object::setTexture(sf::Texture Texture)
{
	texture() = Texture;
}
sf::Texture &Object::texture()
{
	return m_texture;
}

sf::Shape &Object::shape()
{
	return m_shape;
}

sf::RectangleShape &Object::accelerationShape()
{
	return m_accelerationShape;
}

