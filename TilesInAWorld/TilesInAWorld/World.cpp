#include "World.h"

World::World(int WorldWidth, int WorldHeight, float PixelsPerWorldUnit)
{
	WorldTiles[WorldWidth][WorldHeight];
	WorldSize = sf::Vector2f(WorldWidth, WorldHeight);
	for (int x = 0; x < WorldWidth; x++)
	{
		for (int y = 0; y < WorldHeight; y++)
		{
			WorldTiles[x][y] = new Tile(x, y, PixelsPerWorldUnit);
		}
	}
}

void World::RandomizeWorldTiles()
{
	int randNum = 0;
	for (int x = 0;x < (sizeof(WorldTiles) / sizeof(WorldTiles[0]));x++)
	{
		for (int y = 0; y < (sizeof(WorldTiles) / sizeof(WorldTiles[0]));y++)
		{
			randNum = std::rand() % 2;
			if (randNum == 0)
			{
				WorldTiles[x][y].SetTileType(Tile::TileType::Empty);
			}
			else if (randNum == 1)
			{
				WorldTiles[x][y].SetTileType(Tile::TileType::Floor);
			}
		}
	}
}