#pragma once
#include "states.h"
#include <SFML\Graphics.hpp>

struct TileData
{
	int x, y;
	float windowX, windowY, windowXActual, windowYActual, width, height, widthActual, heightActual;
	bool hovered = false;
};

class Tile
{
private:
	TileData data;
	sf::RectangleShape tileShape;
	PrimaryState pState;
	SecondaryState sState;
	void setColor();

public:	
	Tile();
	Tile(int X, int Y);
	Tile(int X, int Y, PrimaryState PState);
	Tile(int X, int Y, PrimaryState PState, SecondaryState sState);
	
	void setX(int newX);
	int getX();
	void setY(int newY);
	int getY();

	void setWindowX(int newX);
	int getWindowX();
	void setWindowY(int newY);
	int getWindowY();

	void hovering(bool hovering);
	bool isHovering();

	void setPrimaryState(PrimaryState newPState);
	PrimaryState getPrimaryState();

	//Sets up the variables that define the location of the tile, and returns the data so it can be checked.
	TileData set(float scale, float camX, float camY);
	void set(TileData& tData);
	sf::RectangleShape shape();

};
