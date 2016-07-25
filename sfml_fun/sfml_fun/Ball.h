#pragma once

#include <SFML\Graphics.hpp>
class Ball
{
private:
	sf::Vector2f m_BallPosition;
	sf::Vector2f m_InitialBallPosition;
	sf::Vector2f m_BallSize;
	float m_BallRadius;

public:
	sf::CircleShape BallShape;
	sf::Vector2f BallMoveAmount;
	Ball();

	float GetRadius();
	sf::Vector2f GetSize();

	sf::Vector2f GetPosition();
	void SetPosition(sf::Vector2f Position);

	void ResetPosition();
};