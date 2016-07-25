#pragma once
#include "Tile.h"

class World
{
public:
	Tile WorldTiles[1][1];
	float WorldWidth;
	float WorldHeight;
private:
	sf::Vector2f WorldSize;
public:
	World(int WorldWidth, int WorldHeight, float PixelsPerWorldUnit);

	void RandomizeWorldTiles();
};