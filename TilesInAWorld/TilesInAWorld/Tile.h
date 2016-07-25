#pragma once
#include <SFML\Graphics.hpp>
class Tile
{
public:
	enum TileType {Empty, Floor};
	sf::RectangleShape TileShape;
private:
	TileType tileType;
	sf::Vector2f Position;
public:
	Tile();
	Tile(float x, float y, float PixelsPerWorldUnit);

	void SetTileType(TileType newTileType);
	TileType GetTileType();
	void SetTilePosition(float x, float y);
	sf::Vector2f GetTilePosition();
};