#include "World.h"

World::World(float Width, float Height, float Scale, double frameRateTimeInterval, float Gravity)
{
	width = Width;
	height = Height;
	scale = Scale;
	gravity = Gravity;

	drawAccelerationMagnitudes = false;

	Timer.setInterval(frameRateTimeInterval);

	trail.setFillColor(sf::Color::Blue);
	trail.setSize(sf::Vector2f(1,1));
}

void World::Update()
{
	Timer.Increment();
	frameTime = Timer.getCurrentFrameTime();
	for (int i = 0; i < Objects.size(); i++)
	{
		Objects.at(i).Update(frameTime, gravity);
		if (Objects.at(i).x() > width || Objects.at(i).y() > height || Objects.at(i).x() + Objects.at(i).width() < 0.f || Objects.at(i).y() + Objects.at(i).height() < 0.f)
		{
			Objects.at(i).isOnScreen(false);
		}
		else
		{
			Objects.at(i).isOnScreen(true);
			Objects.at(i).showacceleration(getdrawAccelerationMagnitude());
		}
	}
}
void World::Draw(sf::RenderWindow &window)
{
	if (window.hasFocus())
	{
		keyPressCheck();
	}
	window.setTitle(std::to_string(getCurrentFrameRate()) + "   ||   " + std::to_string(getCurrentFrameTime()) + "   ||   " + std::to_string(getRunningtime()));
	if (showTrais())
	{
		for (int i = 0; i < Objects.size(); i++)
		{
			for (int j = 0; j < Objects.at(i).gettrail().size(); j++)
			{
				//TODO: only show the last 100 locations in the trail
				trail.setPosition(Objects.at(i).gettrail().at(j));
				window.draw(trail);
			}
		}
	}
	for (int i = 0; i < Objects.size(); i++) 
	{
		if (Objects.at(i).isOnScreen())
		{
			window.draw(Objects.at(i).shape());
		}
	}
	if (getdrawAccelerationMagnitude())
	{
		for (int i = 0; i < Objects.size(); i++)
		{
			if (Objects.at(i).isOnScreen())
			{
				window.draw(Objects.at(i).accelerationShape());
			}
		}
	}
}
void World::keyPressCheck()
{
	//Record how long is has been since the last keypress
	tempKeyInterval += frameTime;
	//Turn on acceleration magnitude
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
	//Reset 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && tempKeyInterval >= keyInterval)
	{
		tempKeyInterval = 0.f;
		//PlaneReset(10.f);
		RandReset(25);
	}
	//show trails 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::T) && tempKeyInterval >= keyInterval)
	{
		tempKeyInterval = 0.f;
		showTrais() = !showTrais();
	}
}
void World::collisionCheck_Broad()
{
	float tempRadii;
	float dist;
	for (int i = 0; i < Objects.size(); i++)
	{
		for (int j = 0; j < Objects.size(); j++)
		{
			tempRadii = Objects.at(i).radius() + Objects.at(j).radius();
			dist = sqrt((abs(Objects.at(i).x() - Objects.at(j).x()) * abs(Objects.at(i).x() - Objects.at(j).x())) + (abs(Objects.at(i).y() - Objects.at(j).y()) * abs(Objects.at(i).y() - Objects.at(j).y())));
			if (dist < tempRadii)
			{

			}
			else
			{
				
			}
		}
	}
}

bool &World::showTrais()
{
	return showtrails;
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
		if (Objects.at(i).isOnScreen())
		{
			Objects.at(i).showacceleration(true);
		}
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

void World::RandReset(int ObjCount, bool clearObjs)
{
	if (clearObjs)
	{
		Objects.clear();
	}
	//TODO: Add method that creates these simple bounds around the screen.
	/*
	//Right side
	addObject(StaticObject(0.f, 0.f, 10.f, 10.f, height));
	//Top
	addObject(StaticObject(10.f, 0.f, 10.f, width - 20, 10.f));
	//Bottom
	addObject(StaticObject(10.f, height - 10.f, 10.f, width - 20.f, 10.f));
	//Left side
	addObject(StaticObject(width - 10.f, 0.f, 10.f, 10.f, height));
	*/

	for (int i = 1; i <= ObjCount; i++)
	{
		DynamicObject temp(10.f, 10.f, 50, 1.f * scale, 1.f * scale);
		temp.setXSpeed((i / (float)ObjCount) * (width / 16));
		temp.setbounciness(i / (ObjCount * 1.1f));
		temp.showacceleration(getdrawAccelerationMagnitude());
		temp.name() = "Object_" + std::to_string(i);
		addObject(temp);
	}
}
void World::PlaneReset(float distFromTop)
{
	Objects.clear();

	//TODO: Add method that creates these simple bounds around the screen.
	/*
	//Right side
	addObject(StaticObject(0.f, 0.f, 10.f, 10.f, height));
	//Top
	addObject(StaticObject(10.f, 0.f, 10.f, width - 20, 10.f));
	//Bottom
	addObject(StaticObject(10.f, height - 10.f, 10.f, width - 20.f, 10.f));
	//Left side
	addObject(StaticObject(width - 10.f, 0.f, 10.f, 10.f, height));
	*/

	for (int i = 0; i < width- 30.f; i += 1.f*scale)
	{
		addObject(DynamicObject(i + 15.f, distFromTop, 50, 1.f * scale, 1.f * scale));
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
