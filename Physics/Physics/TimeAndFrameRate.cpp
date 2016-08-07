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
}

float TimeAndFrameRate::getCurrentFrameRate()
{
	return currentFrameRate;
}

float TimeAndFrameRate::getCurrentFrameTime()
{
	return currentFrameTime;
}