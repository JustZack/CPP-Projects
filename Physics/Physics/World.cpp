#include "World.h"

World::World(float Width, float Height, float Scale, double frameRateTimeInterval, float Gravity)
{
	width = Width;
	height = Height;
	scale = Scale;
	gravity = Gravity;

	drawAccelerationMagnitudes = false;

	Timer.setInterval(frameRateTimeInterval);
}

void World::Update()
{
	Timer.Increment();
	frameTime = Timer.getCurrentFrameTime();
	for (int i = 0; i < Objects.size(); i++)
	{
		Objects.at(i).Update(frameTime, gravity);
	}
}

std::vector<Object> World::getObjects()
{
	return Objects;
}

void World::addObject(Object newObject)
{
	Objects.push_back(newObject);
}

void World::showAccelerationMagnitude()
{
	drawAccelerationMagnitudes = true;
	for (int i = 0; i < Objects.size(); i++)
	{
		Objects.at(i).showacceleration(false);
	}
}
void World::hideAccelerationMagnitude()
{
	drawAccelerationMagnitudes = false;
	for (int i = 0; i < Objects.size(); i++)
	{
		Objects.at(i).showacceleration(false);
	}
}
bool World::getdrawAccelerationMagnitude()
{
	return drawAccelerationMagnitudes;
}

void World::RandReset(int ObjCount)
{
	Objects.clear();
	for (int i = 0; i < ObjCount; i++)
	{
		DynamicObject temp(10.f, 10.f, 50, 1.f * scale, 1.f * scale);
		temp.setXSpeed(i * 1.5f);
		temp.setbounciness(i / (ObjCount * 1.1f));
		addObject(temp);
	}
}
void World::PlaneReset(float distFromTop)
{
	Objects.clear();
	for (int i = 0; i < width; i += 1.f*scale)
	{
		addObject(DynamicObject(1.f, distFromTop, 50, 1.f * scale, 1.f * scale));
	}
}

float World::getCurrentFrameRate()
{
	return Timer.getCurrentFrameRate();
}

float World::getCurrentFrameTime()
{
	return frameTime;
}
void World::setFrameRateInterval(float newInterval)
{
	Timer.setInterval(newInterval);
}

float World::getRunningtime()
{
	return Timer.getRunningtime();
}
