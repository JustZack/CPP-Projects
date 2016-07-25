#include "tile.h"

Tile::Tile(floatPair PixelLocation)
{
	pixelLocation = PixelLocation;
}
Tile::Tile()
{
	pixelLocation = floatPair(0.f,0.f);
}
floatPair Tile::getPixelLocation()
{
	return pixelLocation;
}

void Tile::setPixelLocation(floatPair newPixelLoc)
{
	pixelLocation = newPixelLoc;
}
