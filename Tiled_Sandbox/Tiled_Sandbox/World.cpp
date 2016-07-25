#include "World.h"

World::World()
{
	init(intPair(1, 1), 1.f);
}

World::World(intPair WorldSize, float Scale)
{
	init(WorldSize, Scale);
}

void World::init(intPair WorldSize, float Scale)
{
	worldSize = WorldSize;
	scale = Scale;
	for (int i = 0; i < worldSize.X(); i++)
	{
		//For every column, add a new vector to the existing vector
		allTiles.push_back(std::vector<Tile>());
		for (int j = 0; j < worldSize.Y(); j++)
		{
			//For every row in the current column, add a new tile at its location
			allTiles[i].push_back(Tile(floatPair(i * scale, j * scale)));
		}
	}
}