#pragma once
#include <iostream>
#include "PhysicsObject.h"
#include "Object.h"
#include "Objects.h"
#include "TimeAndFrameRate.h"

class World
{
private:
	//Height and width of the world (Generaly the size of the window that contains it)
	float width, height;
	//The scale of the world. So 1 unit of measurement can equal 1 pixel.
	//for now a unit of measurement is one meter. So one pixel = 1 meter
	float scale;
	//The global variable for gravity. For and Earth based enviroment it should be 9.81m/s 
	float gravity;
	//Boolean determining if any acceleration magnitudes will be draw for objects
	bool drawAccelerationMagnitudes;

	//TODO: Add a collision layer system...
		//This layer sytem would allow specific physics object to only collide with objects on their layer

	//Keeps track off many things having to do with time, such as framerate, and the frame time
	TimeAndFrameRate Timer;
	//Current time the last frame took to render
	float frameTime;

	//Amount of time between keypresses being registered
	float keyInterval = .25f;
	//Temp amount of time that has passed
	float tempKeyInterval = 0.f;

	bool showtrails = false;
	bool &showTrais();
	sf::RectangleShape trail;
public:
	//'array' for any objects in the world
	std::vector<Object> Objects;
	//std::vector<StaticObject> StaticObjects
	World(float Width, float Height, float Scale, double frameRateTimeInterval, float Gravity = 9.81f);

	void Update();
	void Draw(sf::RenderWindow &window);
	void keyPressCheck();
	void collisionCheck_Broad();

	void showAccelerationMagnitude();
	void hideAccelerationMagnitude();
	bool getdrawAccelerationMagnitude();

	std::vector<Object> getObjects();

	void addObject(Object newObject);

	void RandReset(int ObjCount, bool clearObjs = true);
	void PlaneReset(float distFromTop);

	float getCurrentFrameRate();

	float getCurrentFrameTime();
	void setFrameRateInterval(float newInterval);
	float getRunningtime();
};