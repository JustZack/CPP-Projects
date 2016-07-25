#include "Tile.h"
//The constructors
//Default one for making array
Tile::Tile(){}
//The actual constructor we will use
Tile::Tile(float x, float y, float PixelsPerWorldUnit)
{
	Position = sf::Vector2f(x,y);
	tileType = TileType::Empty;
	TileShape.setSize(sf::Vector2f(PixelsPerWorldUnit, PixelsPerWorldUnit));
	SetTilePosition(Position.x * PixelsPerWorldUnit, Position.y * PixelsPerWorldUnit);
}

//Set the tile type of the tile object
void Tile::SetTileType(Tile::TileType newTileType)
{
	tileType = newTileType;
	if (tileType == TileType::Empty)
	{
		TileShape.setFillColor(sf::Color::Transparent);
	
	}
	if (tileType == TileType::Floor)
	{
		TileShape.setFillColor(sf::Color::White);
	}
}
//Get the TileType of the tile object
Tile::TileType Tile::GetTileType()
{
	return tileType;
}
//Set the location of the tile, Generaly only used once at world initialzation
void Tile::SetTilePosition(float x, float y)
{
	TileShape.setPosition(sf::Vector2f(x, y));
}
//Get the location of the tile
sf::Vector2f Tile::GetTilePosition()
{
	return Position;
}