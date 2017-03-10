#include "Tile.h"
#include <iostream>

Tile::Tile()
{

}

Tile::Tile(int X, int Y, PrimaryState PState)
{
	data.x = X; 
	data.y = Y;
	pState = PState;
	tileShape.setPosition(data.x, data.y);
	setColor();
}

TileData Tile::set(float scale, float camX, float camY)
{
	if (!data.hovered)
	{
		data.windowX = (data.x * scale) - camX;
		data.windowY = (data.y * scale) - camY;
		data.width = scale; data.height = scale;

		data.windowXActual = data.windowX;
		data.windowYActual = data.windowY;
		data.widthActual = data.width; data.heightActual = data.height;
	}
	else if (data.hovered)
	{
		data.windowX = (data.x * scale) - camX - data.width / 4;
		data.windowY = (data.y * scale) - camY - data.height / 4;
		data.width = data.widthActual + data.width / 2; data.height = data.heightActual + data.height / 2;
	}
	return data;
}

void Tile::set(TileData& tData)
{
	data.x = tData.x;
	data.y = tData.y;
	data.height = tData.height;
	data.width = tData.width;
}


sf::RectangleShape Tile::shape()
{
	if (tileShape.getPosition().x == data.windowX && tileShape.getPosition().y == data.windowY){}
	else tileShape.setPosition(data.windowX, data.windowY);
	if (data.width == tileShape.getSize().x && data.height == tileShape.getSize().y);
	else tileShape.setSize(sf::Vector2f(data.width, data.height));
	return tileShape;
}

void Tile::hovering(bool hovering)
{
	data.hovered = hovering;
}

bool Tile::isHovering()
{
	return data.hovered;
}

int Tile::getX()
{
	return data.x;
}
void Tile::setX(int newX)
{
	data.x = newX;
}
int Tile::getY()
{
	return data.y;
}
void Tile::setY(int newY)
{
	data.y = newY;
}

void Tile::setWindowX(int newX)
{
	data.windowX = newX;
}
int Tile::getWindowX()
{
	return data.windowX;
}
void Tile::setWindowY(int newY)
{
	data.windowY = newY;
}
int Tile::getWindowY()
{
	return data.windowY;
}

PrimaryState Tile::getPrimaryState()
{
	return pState;
}

void Tile::setPrimaryState(PrimaryState newPState)
{
	pState = newPState;
	setColor();
}

void Tile::setColor()
{
	switch (pState)
	{
	case EMPTY:
		tileShape.setFillColor(sf::Color::Black);
		break;
	case FLOORED:
		tileShape.setFillColor(sf::Color::Blue);
		break;
	case CLICKED:
		tileShape.setFillColor(sf::Color::White);
		break;
	case ERROR:
		tileShape.setFillColor(sf::Color::Red);
		break;
	default:
		tileShape.setFillColor(sf::Color::Magenta);
		std::cout << "Error @" << data.x << ", " << data.y << " | " << getPrimaryState() << std::endl;
		break;
	}
}
