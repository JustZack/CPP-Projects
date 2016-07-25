
#include "ball.h"
#include "Log.h"
#include "Variables.h"

//constructor
Ball::Ball()
{
	BallMoveAmount = sf::Vector2f((WIDTH / BALL_MOVE_AMOUNT_DENOMINATOR) / 2, (WIDTH / BALL_MOVE_AMOUNT_DENOMINATOR) / 2);
	//Save the radius of the ball
	m_BallRadius = HEIGHT / 75;
	m_BallSize = sf::Vector2f(m_BallRadius * 2, m_BallRadius * 2);
	//Set the balls position to the center of the screen
	m_BallPosition = sf::Vector2f((WIDTH / 2) - m_BallRadius, (HEIGHT / 2) - m_BallRadius);
	m_InitialBallPosition = m_BallPosition;

	//Then make the ball the previous radius
	BallShape.setRadius(m_BallRadius);
	//Set the position of the ball
	SetPosition(m_BallPosition);
	
	//Tell me where the ball was created at
	Log("New Ball created at " << m_BallPosition.x << ", " << m_BallPosition.y << ".");
}

//Get the radius and size of the ball
float Ball::GetRadius()
{
	return m_BallRadius;
}
sf::Vector2f Ball::GetSize()
{
	return m_BallSize;
}

//Get and set the position of the ball
sf::Vector2f Ball::GetPosition()
{
	return m_BallPosition;
}
void Ball::SetPosition(sf::Vector2f Position)
{
	m_BallPosition = Position;
	BallShape.setPosition(m_BallPosition);
}

//Reset the position of the ball to center of screen A.K.A. its initial position
void Ball::ResetPosition()
{
	m_BallPosition = m_InitialBallPosition;
	SetPosition(m_BallPosition);
}