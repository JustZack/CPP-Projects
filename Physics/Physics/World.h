#pragma once
#include <iostream>
#include "PhysicsObject.h"
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
	//Boolean determining if trails should be drawn for objects
	bool drawTrails = false;
	//Boolean determining if anything in the world collides with eachother. 
	//there are seperate collision properties for every physics object the determine if they have collision
	bool collisions = true;
	
	int trailLength = 100;
	//TODO: Add a collision layer system...
		//This layer sytem would allow specific physics object to only collide with objects on their layer

	//Keeps track off many things having to do with time, such as framerate, and the frame time
	TimeAndFrameRate tAndfr;
	//Current time the last frame took to render
	float frameTime;

public:
	//'array' for any objects physics will act on
	std::vector<PhysicsObject> PhysicsObjects;
	//'array' for any object that physics will not act on
	//std::vector<StaticObject> StaticObjects
	World(float Width, float Height, float Scale, double frameRateTimeInterval, float Gravity = 9.81f);

	void setDrawTrails(bool drawTrails);
	bool getDrawTrails();
	void setTrailLength(int TrailLength);

	void Update();

	void addPhysObject(PhysicsObject newObject, float xSpeed = 2.5f);
	//void addStaticObject(StaticObject newObject);

	void GeneralReset();
	void RandReset(int ObjCount);
	void PlaneReset(float distFromTop);

	void setCollision(bool Collide);
	bool getCollision();

	std::string getCurrentFrameRate_string();
	float getCurrentFrameRate_float();

	float getCurrentFrameTime();
	void setFrameRateInterval(float newInterval);
	float getRunningtime();


};