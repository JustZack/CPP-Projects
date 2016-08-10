#pragma once
#include <SFML\Graphics.hpp>
class PhysicsObject
{
private:
	float width, height;
	float x, y;
	float mass;
	sf::Color color;

	float xSpeed, ySpeed;

	float bounciness;
	float coefficientOfFriction;
	float acceleration;    // a = sqrt(xSpeed^2 + ypeed^2)   
	float accelerationAngle;
	float PE, KE;

	//These should not be stored in the class itself, and should instead be accessed by refrence from the world.
	float scale;
	float g = 9.81f;
	int windowWidth, windowHeight;
	float trailInterval = .5f;
	float temptrailInterval;

	int trailLength = 100;
	bool drawTrails;
	bool drawAccelerationMagnitude;


	int collisionLayer;
	bool collision;

	void WindowEdgeCollisionCheck(float &frameTime);
	void MathCalculations(float &frameTime);
	void PopulateTrail(float &frameTime);

public:
	//TODO: Make the dots connect
	//Stores a specified amount of the objects previous points
	std::vector <sf::Vector2f> trail;

	PhysicsObject(float Width, float Height, float X, float Y, float Mass, float Bounciness, float CoefficientOfFriction, sf::Color Color = sf::Color::White);

	void Update(float &frameTime);

	sf::Vector2f pos();

	float getXSpeed();
	void setXSpeed(float &newXSpeed);
	float getYSpeed();
	void setYSpeed(float &newYSpeed);

	float getHeight();
	float getWidth();

	void setColor(sf::Color &Color);
	sf::Color getColor();

	//Returns
	std::vector<sf::Vector2f> getPreviousPoints();

	//Sets constants that must be received from a world object, or alternativly could be manualy set.
	void setWorldConstants(float Scale, int WindowWidth, int WindowHeight, float Gravity, int TrailLength);

	//Clears all of the points recorded for the trail
	void clearTrails();
	//Boolean value stating that trails should be shown for this object
	void showTrails();
	//Boolean value stating that trails should not be shown for this object
	void hideTrails();
	//Returns the boolean value determining if trails should be shown.
	bool getdrawTrails();
	//Sets how long between each recording of a location for the trail
	void setTrailInterval(float &interval);
	//Sets how many previous points are recorded to the trail vector.
	void setTrailLength(int &TrailLength);
	//Returns the maximum length of the trail
	int getTrailLength();

	//Determines if this object has collisions
	void setCollision(bool &Collide);
	//Returns the boolean value of the collision variable of the object.
	bool getCollision();

	//Sets which layer of collision the object is on.
	//Only objects on the same layer will collide with eachother
	void setCollisionLayer(int &CollisionLayer);
	//Returns the objects collision layer
	int getCollisionLayer();

	//Returns the angle (direction) of acceleration
	float getAccelerationAngle();
	//Returns the vector of x and y speed
	float getAccelerationMagnitude();

	//allows calculating of the acceleration angle and magnitude
	void showAccelerationMagnitude();
	//Calculating of the acceleration angle and magnitude are no longer done.
	void hideAccelerationMagnitude();
	//Returns the boolean determining if the angle or magnitude are drawn / calculated.
	bool getdrawAccelerationMagnitude();
};