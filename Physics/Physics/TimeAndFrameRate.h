#pragma once
#include <SFML\Graphics.hpp>

class TimeAndFrameRate
{
private:
	//Used to know how many seconds have passed
	sf::Clock clock;
	//The totalruntime of the application
	float totalTime;
	//The interval at which the framerate is updated/calculated
	float timeInterval;
	//Temp time used to calculate avg framerate later
	float tempTime;
	//The total number of frames that have elapsed in the app
	int totalFrameCount;
	//The number of frames that have elapsed over the course of the timeInterval
	int tempFrameCount;

	//The currently calculated framerate
	float currentFrameRate;
	//How long the current frame took to render
	float currentFrameTime;
public:
	//constructor
	TimeAndFrameRate();

	void setInterval(float TimeInterval);

	//Add to the accumulators of the class
	//Called every frame
	void Increment();

	//Return the current framerate
	float getCurrentFrameRate();
	//Return the time that the current frame took
	float getCurrentFrameTime();
	//Return how long the app has been runing
	float getRunningtime();
};