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
	float a;    // a = sqrt(xSpeed^2 + ypeed^2)   
	float PE, KE;

	float scale;
	float g = 9.81f;
	int windowWidth, windowHeight;

	bool drawTrails;
	int trailLength = 25;

	int collisionLayer;
	bool collision;

	void EdgeCollisionCheck();
	void MathCalculations(float &frameTime);
	void PopulateTrails();

public:
	std::vector <sf::Vector2f> prevPoints;

	PhysicsObject(float Width, float Height, float X, float Y, float Mass, float Bounciness, float CoefficientOfFriction, sf::Color Color = sf::Color::White);

	void Update(float &frameTime);

	sf::Vector2f pos();

	void setXSpeed(float &newXSpeed);
	void setYSpeed(float &newYSpeed);

	float getHeight();
	float getWidth();

	void setColor(sf::Color &Color);
	sf::Color getColor();

	std::vector<sf::Vector2f> getPreviousPoints();

	void setWorldConstants(float Scale, int WindowWidth, int WindowHeight, float Gravity);

	void setDrawTrails(bool &drawTrails);
	bool getDrawTrails();

	void setTrailLength(int &TrailLength);
	int getTrailLength();

	void setCollision(bool &Collide);
	bool getCollision();

	void setCollision(int &CollisionLayer);
	int getCollisionLayer();


};