#pragma once
#include <SFML\Graphics.hpp>

//TODO: Use this Object class as the base class for all objects.
class Object
{
private:
	//Location in pixels
	float m_x, m_y;
	//Mass in KG
	float m_mass;
	//Dimensions of the object in pixels * worldScale.
	float m_width, m_height;
	//Velocities in the x and y direction. origional velocities are multiplied by the worldScale.
	float m_xSpeed, m_ySpeed;

	//TODO: Differenciate bounciness and coeficient of friction!
	//Bounciness of the object. Always between 0 and 1. Lower bounciness = less velocity retained. more bounciness = more velocity retained.
	float m_bounciness;
	//Coefficient of friction. Always between 0 and 1. Lower bounciness = less velocity retained. more bounciness = more velocity retained.
	float m_coefficientOfFriction;
	
	//Acceleration vector. This is simply a vector of the xSpeed and ySpeed.
	float m_accelerationMagnitude;
	//Acceleration Angle. This is the direction of the acceleration relative to the object. Angle is based on the way a unit circle is organized.
	float m_accelerationAngle;
	//Boolean that determines if the acceleration angle should be shown for this object.
	bool m_showacceleration;

	//Determines if gravity acts on this object. Defaults to true.
	bool m_isAffectedByGravity = true;

	//Determines if the object collides with any other objects. Defaults to true.
	bool m_hasCollision = true;
	//Interger determining which layer of collision the object is on. Only objects on the same layer collide. Defualts to 0, the first layer.
	int m_collisionLayer = 0;

	//The solid (background) color of the object. Defualts to the color white.
	sf::Color m_color = sf::Color::White;
	//The texture applied to the object.
	sf::Texture m_texture;

	//Creates the object class using data from the constructors.
	void Init(float &X, float &Y, float &Mass, float &Width, float &Height);
	//Updates the position of the object based on gravity and its velocities.
	void Update_Position(float &frameTime, float &g);
	void Update_Acceleration();
public:
	//TODO: Should every object have an on click event asociated with it? 

	//All attrubutes of the object set to 10.f. 
	Object();
	//Initialize a new object with the following attributes.
	Object(float &X, float &Y, float &Mass, float &Width, float &Height);
	

	//Updates the position of the object
	void Update(float &frameTime, float &g); //Not defined in the object class definition, must be defined in the derived class.
	
	//Set the (x, y) pixel position of the object
	void setPosition(float &X, float &Y); 
	//Return the value for the x location of the object
	float &x();
	//Return the value for the y location of the object
	float &y();

	//Set the mass of the object in KG
	void setMass(float &Mass); 
	//Return the mass of the object
	float &mass();

	//Set the dimensions of the object.
	void setDimensions(float &Width, float &Height);
	//Return the width of the object.
	float &width();
	//Return the height of the object
	float &height();

	//Set the velocity of the object along the X-Axis.
	void setXSpeed(float &XSpeed);
	//Return the velocity of the object along X-Axis.
	float &xSpeed();
	//Set the velocity of the object along the Y-Axis.
	void setYSpeed(float &YSpeed);
	//Return the velocity of the object along Y-Axis.
	float &ySpeed();

	//Returns the acceleration magnitude, which is the vector of the x and y speed.
	float &accelerationMagnitude();
	//Returns the acceleration angle.
	float &accelerationAngle();
	//Determines if the acceleration of this object should be shown.
	void showacceleration(bool &ShowAcceleration);
	//Returns the value of whether or not the acceleration should be shown for this object.
	bool &showacceleration();

	//Sets the bounciness of the object. Must be between 0 and 1.
	void setbounciness(float &Bounciness);
	//Returns the bounciness of the object. Always a value between 0 and 1.
	float &bounciness();

	//Sets the coefficient of friction for the object. Must be between 0 and 1.
	void setcoefficientOfFriction(float &CoefficientOfFriction);
	//Returns the coefficient of friction for the object. Always between 0 and 1.
	float &coefficientOfFriction();

	//Determines if the object is affected by gravity. true->Affected by gravity | false->Not affected by gravity.
	void isAffectedByGravity(bool &AffectedByGravity);
	//Returns the value of whether or not the object is affected by gravity.
	bool &isAffectedByGravity();

	//Determines if the object collides with other colliding objects.
	void hasCollision(bool &Collides);
	//Returns the value of whether or not the object has collision.
	bool &hasCollision();

	//Determines what the collision layer for the object is.
	void setCollisionLayer(int &CollisionLayer);
	//Returns the collision layer number. 0 by default.
	int &collisionLayer();

	//Set the color of the object.
	void setColor(sf::Color &Color);
	//Returns the color of the object.
	sf::Color &color();

	//Set the texture of the object.
	void setTexture(sf::Texture &Texture);
	//Returns the texture of the object.
	sf::Texture &texture();
};