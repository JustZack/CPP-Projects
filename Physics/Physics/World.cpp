#include "World.h"

World::World(float Width, float Height, float Scale, double frameRateTimeInterval, float Gravity)
{
	width = Width;
	height = Height;
	scale = Scale;
	gravity = Gravity;

	tAndfr.setInterval(frameRateTimeInterval);
}

void World::Update()
{
	tAndfr.Increment();
	frameTime = tAndfr.getCurrentFrameTime();
	for (int i = 0; i < PhysicsObjects.size(); i++)
	{
		PhysicsObjects.at(i).Update(frameTime);
	}
}

void World::addPhysObject(PhysicsObject newObject, float xSpeed)
{
	newObject.setWorldConstants(scale, width, height, gravity);
	newObject.setXSpeed(xSpeed);
	newObject.setDrawTrails(drawTrails);
	PhysicsObjects.push_back(newObject);
}

void World::setDrawTrails(bool DrawTrails)
{
	drawTrails = DrawTrails;
	for (int i = 0; i < PhysicsObjects.size(); i++)
	{
		PhysicsObjects.at(i).setDrawTrails(drawTrails);
	}
}
bool World::DrawTrails()
{
	return drawTrails;
}

void World::RandReset(int ObjCount)
{
	PhysicsObjects.clear();
	for (int i = 0; i < ObjCount; i++)
	{
		addPhysObject(PhysicsObject(5.f, 5.f, 10.f, 10.f, 500, i / (ObjCount * 1.1f),1,sf::Color::Red), i);
	}
}

void World::setCollision(bool Collide)
{
	collisions = Collide;
	for (int i = 0; i < PhysicsObjects.size(); i++)
	{
		PhysicsObjects.at(i).setCollision(collisions);
	}
}
bool World::getCollision()
{
	return collisions;
}

std::string World::getCurrentFrameRate_string()
{
	return std::to_string(tAndfr.getCurrentFrameRate());
}
float World::getCurrentFrameRate_float()
{
	return tAndfr.getCurrentFrameRate();
}