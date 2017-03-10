#pragma once
#include "Tile.h"
#include "TimeAndFrameRate.h"
#include "EventQueue.h"
#include <vector>
#include <SFML\Graphics.hpp>
#include <thread>
//TODO: create 'event' queue.
//This queue will tell the window actions it needs to complete, which will be added via an input thread.

class World
{
private:
	std::vector<std::vector<Tile>> tiles;
	int gridWidth, gridHeight;
	float windowWidth, windowHeight;
	float MAX_SCALE = -1;
	float MIN_SCALE = 5.f;
	float cameraX = 0.0, cameraY = 0.0;
	float scale = 10.f;

	const float ZOOM_AMOUNT = 100.f;
	const float MOVE_AMOUNT = 500.f;

	const sf::RenderWindow &rw;
	
	bool goStart = false;
	bool runInput = true;
	std::thread inputThread;
	EventQueue eventQueue;
	eInfo eTemp;

	TimeAndFrameRate frameRateTimer;
	float currentFrameTime;

	TileData data;
	Tile tempTile;

	int hoverI = -1, hoverJ = -1;

	void init(int Width, int Height);
public:
	World(int Width, int Height, const sf::RenderWindow &w);
	World(int Width, int Height, float Scale, const sf::RenderWindow &w);

	void start();
	void input();
	void update();
	void draw(sf::RenderWindow &w);
	void close();
};