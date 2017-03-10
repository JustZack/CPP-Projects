#include "TimeAndFrameRate.h"
#include <iostream>

TimeAndFrameRate::TimeAndFrameRate()
{
	totalTime = .0f;
	timeInterval = 1.0f;
	tempTime = .0f;
	currentFrameRate = .0f;

	totalFrameCount = 0;
	tempFrameCount = 0;

	frameRateText.setPosition(0, 0);
	frameRateText.setFillColor(sf::Color::Green);
	frameRateText.setStyle(sf::Text::Regular);
	frameRateText.setCharacterSize(15);
	font.loadFromFile("arial.ttf");
	frameRateText.setFont(font);
}

void TimeAndFrameRate::setInterval(float TimeInterval)
{
	timeInterval = TimeInterval; 
}

void TimeAndFrameRate::Increment()
{
	currentFrameTime = clock.restart().asSeconds();

	totalTime += currentFrameTime;
	tempTime += currentFrameTime;
	totalFrameCount++;
	tempFrameCount++;
	if (tempTime >= timeInterval)
	{
		currentFrameRate = tempFrameCount / tempTime;
		tempFrameCount = 0;
		tempTime = 0.f;
	}
	frameRateText.setString(std::to_string((int)currentFrameRate));
}

float TimeAndFrameRate::getCurrentFrameRate()
{
	return currentFrameRate;
}

float TimeAndFrameRate::getCurrentFrameTime()
{
	return currentFrameTime;
}

float TimeAndFrameRate::getRunningtime()
{
	return totalTime;
}

sf::Text& TimeAndFrameRate::text()
{
	return frameRateText;
}

void TimeAndFrameRate::Reset()
{
	totalTime = 0.f;
}
