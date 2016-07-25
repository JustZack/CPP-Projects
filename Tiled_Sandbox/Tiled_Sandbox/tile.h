#pragma once
#include <SFML\Graphics.hpp>
#include "util.h"

class Tile
{
private:
	floatPair pixelLocation;

public:
	Tile(floatPair PixelLocation);
	Tile();
	floatPair getPixelLocation();
	void setPixelLocation(floatPair newPixelLoc);
};