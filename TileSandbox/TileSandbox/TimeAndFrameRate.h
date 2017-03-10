#pragma once
#include <SFML\Graphics.hpp>

class TimeAndFrameRate
{
private:
	//Used to know how many seconds have passed
	sf::Clock clock;
	//Font of the framerate text
	sf::Font font;
	//text used to draw the fps
	sf::Text frameRateText;
	//The totalruntime of the application
	float totalTime;
	//The interval at which the framerate is updated/calculated
	float timeInterval = .5f;
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

	//Add to the accumulators of the object
	//Called every frame
	void Increment();

	//Return the current framerate
	float getCurrentFrameRate();
	//Return the time that the current frame took
	float getCurrentFrameTime();
	//Return how long the app (specificaly this object) has been runing (instansiated)
	float getRunningtime();

	sf::Text& text();

	void Reset();
};