#pragma once

#include <SFML\Graphics.hpp>
#include "paddle.h"
#include "collision.h"
#include "variables.h"

void PlayerOneInput(Paddle &_paddle)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		if (PaddleCollision(_paddle) == 1)
		{

		}
		else
		{

			//Move the paddle up
			_paddle.SetPosition(sf::Vector2f(_paddle.GetPosition().x, _paddle.GetPosition().y - _paddle.PaddleMoveAmount));
			Log_Fast("Player one's paddle moved to " << _paddle.GetPosition().x << ", " << _paddle.GetPosition().y);
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		if (PaddleCollision(_paddle) == 2)
		{

		}
		else
		{
			//Move the paddle down
			_paddle.SetPosition(sf::Vector2f(_paddle.GetPosition().x, _paddle.GetPosition().y + _paddle.PaddleMoveAmount));
			Log_Fast("Player one's paddle moved to " << _paddle.GetPosition().x << ", " << _paddle.GetPosition().y);
		}
	}
}
void PlayerTwoInput(Paddle &_paddle)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		if (PaddleCollision(_paddle) == 1)
		{

		}
		else
		{

			//Move the paddle up
			_paddle.SetPosition(sf::Vector2f(_paddle.GetPosition().x, _paddle.GetPosition().y - _paddle.PaddleMoveAmount));
			Log_Fast("Player two's paddle moved to " << _paddle.GetPosition().x << ", " << _paddle.GetPosition().y);
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		if (PaddleCollision(_paddle) == 2)
		{

		}
		else
		{
			//Move the paddle down
			_paddle.SetPosition(sf::Vector2f(_paddle.GetPosition().x, _paddle.GetPosition().y + _paddle.PaddleMoveAmount));
			Log_Fast("Player two's paddle moved to " << _paddle.GetPosition().x << ", " << _paddle.GetPosition().y);
		}
	}
}
//check for input for each paddle
void PlayerInput(Paddle &_paddle)
{
	if (_paddle.m_Player == 1)
	{
		//check for player one movement
		PlayerOneInput(_paddle);
	}
	if (_paddle.m_Player == 2)
	{
		//check for player Two movement
		PlayerTwoInput(_paddle);
	}
}