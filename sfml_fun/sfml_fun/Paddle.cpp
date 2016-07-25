
#include "Paddle.h"
#include "Log.h"
#include "Variables.h"


Paddle::Paddle(float SideOffset, unsigned short Player)
{
	//Save paddle size
	m_PaddleSize = sf::Vector2f(WIDTH / 90, HEIGHT / 10);
	PaddleMoveAmount = HEIGHT / PADDLE_MOVE_AMOUNT_DENOMINATOR;

	//check if the paddle is the far left or right paddle (player one or two)
	if (Player == 1)
	{
		m_Player = 1;
		//Set the paddle to be on the Wfar left side
		m_PaddlePosition = sf::Vector2f(SideOffset, (HEIGHT / 2) - (m_PaddleSize.y / 2));
	}
	else if (Player == 2)
	{
		//Save the which player is controlling the paddle
		m_Player = 2;
		//Set paddle to be on the far left side
		m_PaddlePosition = sf::Vector2f(WIDTH - (SideOffset + m_PaddleSize.x), (HEIGHT / 2) - (m_PaddleSize.y / 2));
	}

	//Save the defualt position for the paddle
	m_InitialPaddlePosition = m_PaddlePosition;

	
	//Setup the actual paddle 'object'
	//Set its size
	PaddleShape.setSize(m_PaddleSize);
	//Set its position
	SetPosition(m_PaddlePosition);

	//Tell me where the paddles was created at
	Log("New Paddle created at " << m_PaddlePosition.x << ", " << m_PaddlePosition.y << ".");
}
//Get the size of the paddle
sf::Vector2f Paddle::GetSize()
{
	return m_PaddleSize;
}

//Get and set the position of the paddle
sf::Vector2f Paddle::GetPosition()
{
	return m_PaddlePosition;
}
void Paddle::SetPosition(sf::Vector2f Position)
{
	m_PaddlePosition = Position;
	PaddleShape.setPosition(m_PaddlePosition);
}

//Reset the position of the paddles to its defualt position.
void Paddle::ResetPosition()
{
	//Reset the paddles position to the initial position
	m_PaddlePosition = m_InitialPaddlePosition;
	SetPosition(m_PaddlePosition);
}