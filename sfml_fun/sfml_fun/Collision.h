#pragma once

#include "paddle.h"
#include "ball.h"
#include "Variables.h"

int LastPlayerToHitTheBall;

int PaddleCollision(Paddle &_paddle)
{
	//Check if the paddles position is out of bounds
	
	//Top of screen
	if (_paddle.GetPosition().y <= 0)
	{
		Log_Fast("Player " << _paddle.m_Player << "'s paddle reached the top of screen");
		return 1;
	}
	//bottom of screen
	if (_paddle.GetPosition().y >= HEIGHT - _paddle.GetSize().y)
	{
		Log_Fast("Player " << _paddle.m_Player << "'s paddle reached the bottom of screen");
		return 2;
	}
	//No collisions here!
	return 0;
}

bool BallCollision(Ball &_ball)
{
	//Left side of screen
	//Game ends
	if (_ball.GetPosition().x <= 0.f)
	{
		Log("Ball hit the left side of the screen");
		return true;
	}
	//Top of screen
	if (_ball.GetPosition().y <= 0.f)
	{
		Log("Ball bounced off of top of screen");
		_ball.BallMoveAmount.y *= -1;
		return false;
		//Collision with top of screen, so bounce
	}
	//Right side of screen
	//Game ends
	if (_ball.GetPosition().x >= WIDTH - (_ball.GetSize().x))
	{
		Log("Ball hit the right side of the screen");
		return true;
	}
	//bottom of screen
	if (_ball.GetPosition().y >= HEIGHT - (_ball.GetSize().y))
	{
		Log("Ball bounced off of bottom of screen");
		_ball.BallMoveAmount.y *= -1;
		return false;
		//Collision with bottom of screen, so bounce
	}
	//No collision here, So dont end the game!
	return false;
}

bool PaddleAndBallCollision(Paddle &_paddle, Ball &_ball)
{
	if (_paddle.m_Player == 1)
	{
		//Check if the ball is within the bounds of the paddle
		if (   _ball.GetPosition().x >= _paddle.GetPosition().x
			&& _ball.GetPosition().x <= _paddle.GetPosition().x + _paddle.GetSize().x 
			&& _ball.GetPosition().y + _ball.GetSize().y >= _paddle.GetPosition().y
			&& _ball.GetPosition().y <= _paddle.GetPosition().y + _paddle.GetSize().y)
		{
			//The ball hit the left side paddle
			Log("Player " << _paddle.m_Player << " hit the ball");
			//Save who just hit the ball
			LastPlayerToHitTheBall = 1;
			//Invert the movment along the X axis to go the opposite direction
			_ball.BallMoveAmount.x *= -1;
			_ball.SetPosition(sf::Vector2f(_paddle.GetPosition().x + _paddle.GetSize().x, _ball.GetPosition().y));
			return true;
		}
		else
		{
			//The ball did not hit the players paddle
			return false;
		}
	}
	else if (_paddle.m_Player == 2)
	{
		//Check if the ball is within the bounds of the paddle
		if (   _ball.GetPosition().x + _ball.GetSize().x >= _paddle.GetPosition().x 
			&& _ball.GetPosition().x + _ball.GetSize().x <= _paddle.GetPosition().x + _paddle.GetSize().x
			&& _ball.GetPosition().y + _ball.GetSize().x >= _paddle.GetPosition().y 
			&& _ball.GetPosition().y <= _paddle.GetPosition().y + _paddle.GetSize().y)
		{
			//The ball hit the right side paddle
			Log("Player " << _paddle.m_Player << " hit the ball");
			//Save who just hit the ball
			LastPlayerToHitTheBall = 2;
			//Invert the movment along the X axis to go the opposite direction
			_ball.BallMoveAmount.x *= -1;
			_ball.SetPosition(sf::Vector2f(_paddle.GetPosition().x - _ball.GetSize().x, _ball.GetPosition().y));
			return true;
		}
		else
		{
			//The ball did not hit the players paddle
			return false;
		}
	}
	//If the code made it here there may be a problem
	Log("Error: Incorrect parameter for PaddleAndBallCollision for _paddle");
	return false;
}