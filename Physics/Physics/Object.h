#pragma once
#include <SFML\Graphics.hpp>

//TODO: Use this Object class as the base class for all objects.
class Object
{
private:
	//Location in pixels
	float x, y;
	//Mass in KG
	float mass;
	//Dimensions of the object in pixels * worldScale.
	float width, height;
	//Velocities in the x and y direction. origional velocities are multiplied by the worldScale.
	float xSpeed, ySpeed;
	//Determines if gravity acts on this object. Defaults to true.
	bool isAffectedByGravity = true;
	//Determines if the object collides with any other objects. Defaults to true.
	bool hasCollision = true;
	//Interger determining which layer of collision the object is on. Only objects on the same layer collide. Defaults to 0, the first layer.
	int collisionLayer = 0;
	//The solid (background) color of the object. Defualts to the color white.
	sf::Color color = sf::Color::White;
	//The texture applied to the object.
	sf::Texture texture;

public:
	//TODO: Should every object have an on click event asociated with it? 

	//All attrubutes of the object set to 10.f. 
	Object();
	//Initialize a new object with the following attributes.
	Object(float &X, float &Y, float &Mass, float &Width, float &Height);

	//Set the (x, y) pixel position of the object
	void setPosition(float &X, float &Y); 
	//Return the value for the x location of the object
	float x(); 
	//Return the value for the y location of the object
	float y(); 

	//Set the mass of the object in KG
	void setMass(float &Mass); 
	//Return the mass of the object
	float mass();

	//Set the dimensions of the object.
	void setDimensions(float &Width, float &Height);
	//Return the width of the object.
	float width();
	//Return the height of the object
	float height();

	//Set the velocity of the object along the X-Axis.
	void setXSpeed(float &XSpeed);
	//Return the velocity of the object along X-Axis.
	float xSpeed();
	//Set the velocity of the object along the Y-Axis.
	void setYSpeed(float &YSpeed);
	//Return the velocity of the object along Y-Axis.
	float ySpeed();

	//Determines if the object is affected by gravity. true->Affected by gravity | false->Not affected by gravity.
	void isAffectedByGravity(bool &AffectedByGravity);
	//Returns the value of whether or not the object is affected by gravity.
	bool isAffectedByGravity();

	//Determines if the object collides with other colliding objects.
	void hasCollision(bool &Collides);
	//Returns the value of whether or not the object has collision.
	bool hasCollision();

	//Determines what the collision layer for the object is.
	void setCollisionLayer(int CollisionLayer);
	//Returns the collision layer number. 0 by default.
	int collisionLayer();

	//Set the color of the object.
	void setColor(sf::Color Color);
	//Returns the color of the object.
	sf::Color color();

	//Set the texture of the object.
	void setTexture(sf::Texture Texture);
	//Returns the texture of the object.
	sf::Texture texture();
};