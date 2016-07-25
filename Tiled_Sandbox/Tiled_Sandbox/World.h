#pragma once
#include "util.h"
#include "tile.h"
#include <iostream>
class World
{
private:
	intPair worldSize;
	float scale;
	std::vector< std::vector<Tile> > allTiles;
	//<still need an std::vector< std::vector<Tile> > here>.
	//http://www.cplusplus.com/forum/general/833/
public:
	World();
	World(intPair WorldSize, float Scale);
private:
	void init(intPair WorldSize, float Scale);
};