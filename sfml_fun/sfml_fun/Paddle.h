#pragma once

#include <SFML\Graphics.hpp>

class Paddle
{
private:
	sf::Vector2f m_PaddleSize;
	sf::Vector2f m_PaddlePosition;
	sf::Vector2f m_InitialPaddlePosition;
public:
	sf::RectangleShape PaddleShape;
	int m_Player;
	float PaddleMoveAmount;

	Paddle(float SideOffset, unsigned short Player);

	sf::Vector2f GetSize();

	sf::Vector2f GetPosition();
	void SetPosition(sf::Vector2f Position);

	void ResetPosition();
};