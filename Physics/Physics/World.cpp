#include "World.h"

World::World(float Width, float Height, float Scale, double frameRateTimeInterval, float Gravity)
{
	width = Width;
	height = Height;
	scale = Scale;
	gravity = Gravity;

	drawAccelerationMagnitudes = false;

	Timer.setInterval(frameRateTimeInterval);

	addObject(StaticObject(0.f,0.f,10.f,10.f,height));
	addObject(StaticObject(0.f, 0.f, 10.f, width, 10.f));
	addObject(StaticObject(0.f, height - 10.f, 10.f, width, 10.f));
	addObject(StaticObject(width - 10.f, 0.f, 10.f, 10.f, 900.f));

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
void World::Draw(sf::RenderWindow &window)
{
	if (window.hasFocus())
	{
		keyPressCheck();
	}
	window.setTitle(std::to_string(getCurrentFrameRate()) + "   ||   " + std::to_string(getCurrentFrameTime()) + "   ||   " + std::to_string(getRunningtime()));
	for (int i = 0; i < Objects.size(); i++) 
	{
		window.draw(Objects.at(i).shape());
	}
	if (getdrawAccelerationMagnitude())
	{
		for (int i = 0; i < Objects.size(); i++)
		{
			window.draw(Objects.at(i).accelerationShape());
		}
	}
}
void World::keyPressCheck()
{
	tempKeyInterval += frameTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && tempKeyInterval >= keyInterval)
	{
		tempKeyInterval = 0.f;
		if (getdrawAccelerationMagnitude())
		{
			hideAccelerationMagnitude();
		}
		else if (!getdrawAccelerationMagnitude())
		{
			showAccelerationMagnitude();
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && tempKeyInterval >= keyInterval)
	{
		tempKeyInterval = 0.f;
		RandReset(100);
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
	//Objects.clear();
	for (int i = 0; i < ObjCount; i++)
	{
		DynamicObject temp(10.f, 10.f, 50, 1.f * scale, 1.f * scale);
		temp.setXSpeed(i);
		temp.setbounciness(i / (ObjCount * 1.1f));
		addObject(temp);
	}
}
void World::PlaneReset(float distFromTop)
{
	Objects.clear();
	for (int i = 0; i < width; i += 1.f*scale)
	{
		addObject(DynamicObject(i, distFromTop, 50, 1.f * scale, 1.f * scale));
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
