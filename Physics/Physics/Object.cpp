#include "Object.h"
#define _USE_MATH_DEFINES 
#include <math.h>

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
}
Object::Object()
{
	float f = 10.f;
	Init(f, f, f, f, f);
}
Object::Object(float &X, float &Y, float &Mass, float &Width, float &Height)
{
	Init(X, Y, Mass, Width, Height);
}

void Object::Update(float &frameTime, float &g)
{
	Update_Position(frameTime, g);
	Update_Acceleration();
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
		float tempYspeed = ySpeed();
		tempYspeed += g * frameTime;
		setYSpeed(tempYspeed);
	}
	//Save temp x and y values to send to the setPosition() method after wards.
	//Required because this method takes everything by refrence.
	float tempX = x() + (xSpeed() * frameTime), tempY = y() + (ySpeed() * frameTime);
	setPosition(tempX, tempY);
}
void Object::Update_Acceleration()
{
	//Object is mocing straight down or up.
	if (abs(xSpeed()) == 0 && abs(ySpeed()) > 0)
	{
		accelerationMagnitude() = ySpeed();
		//Object is moving down
		if (ySpeed() > 0)
		{
			accelerationAngle() = 270.f;
		}
		//Object is moving up
		else if (ySpeed() < 0)
		{
			accelerationAngle() = 90.f;
		}

	}
	//Object is moving straight left or right.
	else if (abs(ySpeed()) == 0 && abs(xSpeed()) > 0)
	{
		accelerationMagnitude() = xSpeed();
		//Object is moving right
		if (xSpeed() > 0)
		{
			accelerationMagnitude() = 0.f;
		}
		//Object is moving right
		else if (xSpeed() < 0)
		{
			accelerationMagnitude() = 180.f;
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
	}
}

void Object::setPosition(float &X, float &Y)
{
	x() = X;
	y() = Y;
}
float &Object::x()
{
	return m_x;
}
float &Object::y()
{
	return m_y;
}

void Object::setMass(float &Mass)
{
	mass() = Mass;
}
float &Object::mass()
{
	return m_mass;
}

void Object::setDimensions(float &Width, float &Height)
{
	width() = Width;
	height() = Height;
}
float &Object::width()
{
	return m_width;
}
float &Object::height()
{
	return m_height;
}

void Object::setXSpeed(float &XSpeed)
{
	xSpeed() = XSpeed;
}
float &Object::xSpeed()
{
	return m_xSpeed;
}
void Object::setYSpeed(float &YSpeed)
{
	ySpeed() = YSpeed;
}
float &Object::ySpeed()
{
	return m_ySpeed;
}

float &Object::accelerationMagnitude()
{
	return m_accelerationMagnitude;
}
float &Object::accelerationAngle()
{
	return m_accelerationAngle;
}
void Object::showacceleration(bool &ShowAcceleration)
{
	showacceleration() = ShowAcceleration;
}
bool &Object::showacceleration()
{
	return m_showacceleration;
}

void Object::setbounciness(float &Bounciness)
{
	bounciness() = Bounciness;
}
float &Object::bounciness()
{
	return m_bounciness;
}

void Object::setcoefficientOfFriction(float &CoefficientOfFriction)
{
	coefficientOfFriction() = CoefficientOfFriction;
}
float &Object::coefficientOfFriction()
{
	return m_coefficientOfFriction;
}

void Object::isAffectedByGravity(bool &AffectedByGravity)
{
	isAffectedByGravity() = AffectedByGravity;
}
bool &Object::isAffectedByGravity()
{
	return m_isAffectedByGravity;
}

void Object::hasCollision(bool &Collides)
{
	hasCollision() = Collides;
}
bool &Object::hasCollision()
{
	return m_hasCollision;
}

void Object::setCollisionLayer(int &CollisionLayer)
{
	collisionLayer() = CollisionLayer;
}
int &Object::collisionLayer()
{
	return m_collisionLayer;
}

void Object::setColor(sf::Color &Color)
{
	color() = Color;
}
sf::Color &Object::color()
{
	return m_color;
}

void Object::setTexture(sf::Texture &Texture)
{
	texture() = Texture;
}
sf::Texture &Object::texture()
{
	return m_texture;
}
