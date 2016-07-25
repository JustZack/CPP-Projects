
//The sfml lib we need in order to draw
#include <SFML/Graphics.hpp>
//Two headers we need in order to make the thread sleep
#include <chrono>
#include <thread>
//Used to make a list AKA vector
#include <vector>
//Used to Log(message) things
#include "Log.h"
//Ball and paddle objects
#include "Paddle.h"
#include "ball.h"
//Methods to resolve where the ball or paddle collided
#include "collision.h"
//Methods to move the ball around
#include "PlayerInput.h"
//Height and width of screen variables defined
#include "Variables.h"
//Used to calculate framerate
#include "windows.h"

//Player paddles initilization
Paddle PlayerOne(25.f, 1);
Paddle PlayerTwo(25.f, 2);
//The ball for pong initialzation
Ball PongBall;

//Text objects used to display the score of each player
sf::Text PlayerOneScoreShape;
sf::Text PlayerTwoScoreShape;
//Font used for the objects above
sf::Font font;

//Player scores
int PlayerOneScore = 0;
int PlayerTwoScore = 0;
//Checks if it is the first time through the loop since reset
bool FirstTimeThroughLoop = true;

//Reset the paddles and the balls positions
void ResetPositions()
{
	PlayerOne.ResetPosition();
	PlayerTwo.ResetPosition();
	PongBall.ResetPosition();

	PlayerOneScoreShape.setString(std::to_string(PlayerOneScore));
	PlayerTwoScoreShape.setString(std::to_string(PlayerTwoScore));


	LastPlayerToHitTheBall = 3;

	FirstTimeThroughLoop = true;
}
//Checks for paddle and ball colllisions
void Collisions()
{
	


	//Check for ONLY ball collisions
	if (BallCollision(PongBall))
	{
		if (LastPlayerToHitTheBall == 1)
		{
			//Give player one a point because player two missed
			PlayerOneScore++;
			Log("Player Ones's score is now " << PlayerOneScore);
			if (PongBall.BallMoveAmount.x > 0)
			{
				PongBall.BallMoveAmount.x *= -1;
			}
		}
		if (LastPlayerToHitTheBall == 2)
		{
			//Give player two a point because player one missed
			PlayerTwoScore++;
			Log("Player Two's score is now " << PlayerTwoScore);
			if (PongBall.BallMoveAmount.x < 0)
			{
				PongBall.BallMoveAmount.x *= -1;
			}
		}
		Log("Round ended" << std::endl);
		ResetPositions();
	}
	//Check for both paddle and ball collision
	//Player one and ball collisions
	PaddleAndBallCollision(PlayerOne, PongBall);
	//Player two and ball collisions
	PaddleAndBallCollision(PlayerTwo, PongBall);
}
//Sets up the text objects
void SetupTextObjects()
{
	//Setup the size of the numbers
	PlayerOneScoreShape.setCharacterSize(HEIGHT / 10);
	PlayerTwoScoreShape.setCharacterSize(HEIGHT / 10);
	//Setup the position of the objects on the screen
	PlayerOneScoreShape.setPosition(sf::Vector2f((WIDTH / 2) - (PlayerOneScoreShape.getCharacterSize() * 2), 10.f));
	PlayerTwoScoreShape.setPosition(sf::Vector2f((WIDTH / 2) + (PlayerOneScoreShape.getCharacterSize() * 2), 10.f));
	//Set the font of both objects
	PlayerOneScoreShape.setFont(font);
	PlayerTwoScoreShape.setFont(font);
	//Make sure they are normal text, not italic, bold, or underlined
	PlayerOneScoreShape.setStyle(sf::Text::Regular);
	PlayerTwoScoreShape.setStyle(sf::Text::Regular);
	//Make the colors of them red
	PlayerOneScoreShape.setColor(sf::Color::Red);
	PlayerTwoScoreShape.setColor(sf::Color::Green);
	//Make them both say the scores of their players
	PlayerOneScoreShape.setString(std::to_string(PlayerOneScore));
	PlayerTwoScoreShape.setString(std::to_string(PlayerTwoScore));
}
//Check for autoplay and input
void AutoPlayAndInput()
{
	//Check if the autoplay feature is enabled
	//Either it is, or both paddles are
	if (AUTOPLAY_BOTH || (AUTOPLAY_L && AUTOPLAY_R))
	{
		PlayerOne.SetPosition(sf::Vector2f(PlayerOne.GetPosition().x, PongBall.GetPosition().y - ((PlayerOne.GetSize().y / 2) - PongBall.GetSize().y / 2)));
		PlayerTwo.SetPosition(sf::Vector2f(PlayerTwo.GetPosition().x, PlayerOne.GetPosition().y));
	}
	//Only one of the paddles are set to autoplay
	else if (AUTOPLAY_L || AUTOPLAY_R)
	{
		if (AUTOPLAY_L)
		{
			PlayerOne.SetPosition(sf::Vector2f(PlayerOne.GetPosition().x, PongBall.GetPosition().y - ((PlayerOne.GetSize().y / 2) - PongBall.GetSize().y / 2)));
			PlayerInput(PlayerTwo);
		}
		if (AUTOPLAY_R)
		{
			PlayerTwo.SetPosition(sf::Vector2f(PlayerTwo.GetPosition().x, PongBall.GetPosition().y - ((PlayerTwo.GetSize().y / 2) - PongBall.GetSize().y / 2)));
			PlayerInput(PlayerOne);
		}
	}
	//No autoplay enabled
	else
	{
		PlayerInput(PlayerOne);
		PlayerInput(PlayerTwo);
	}
}
//Pause Debug
void DebugPause()
{
	//if debug is on
	if (DEBUG == 1)
	{
		//If the spacebar was pressed...
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		{
			//Let us know the game was paused
			Log("Game Paused")
			//Wait until the user releases the spacebar
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
			{
				//Wait for awhile so the CPU is not used fully while the 
				//Spacebar is pressed
				std::this_thread::sleep_for(std::chrono::milliseconds(25));
			}
			//Let us know the game was unpaused
			Log("Game Resumed");
		}
	}
}
//Main entry point for the program
int main()
{
	//loads up the font I put in the project folder into the font object
	font.loadFromFile("arial.ttf");
	//Setup the text objects for the players score
	SetupTextObjects();

	PongBall.BallShape.setFillColor(sf::Color::Blue);

	//Setup the window that will display pong
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Pong");
	//Set the maximum framerate for the entire window. Keeps things moving right along...
	window.setFramerateLimit(60);
	//Tell the user the amount of movement the paddle will have per frame
	Log("Ball and Paddle move amout are set to " << HEIGHT / BALL_MOVE_AMOUNT_DENOMINATOR << std::endl);
	

	//Just make a space between the previous output and the ones that may follow it.
	std::cout << std::endl;

	//Sleep for 1 second
	//Sleep for 1000 miliseconds
	//Sleep for 1 million microseconds
	long SleepTime = 1000;

	//While the window is open....
	while (window.isOpen())
	{
		#pragma region Drawing to the window 
		//Clear up, draw to, and display the new frame for the window.
		window.clear();
		window.draw(PlayerOneScoreShape);
		window.draw(PlayerTwoScoreShape);
		window.draw(PlayerOne.PaddleShape);
		window.draw(PlayerTwo.PaddleShape);
		window.draw(PongBall.BallShape);
		window.display();
		#pragma endregion

		//Calculate the position of the ball
		PongBall.SetPosition(sf::Vector2f(PongBall.GetPosition().x + PongBall.BallMoveAmount.x / 2, PongBall.GetPosition().y + PongBall.BallMoveAmount.y));
		

		//Used for the initial startup, and a reset of the game
		if (FirstTimeThroughLoop)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(SleepTime));
			FirstTimeThroughLoop = false;
		}
		//Log the balls position every frame
		Log_Fast("Balls position moved to " << PongBall.GetPosition().x << ", " << PongBall.GetPosition().y);
		//Used in the while loop bellow
		sf::Event event;
		//Checks for any events that may have occured in the window
		while (window.pollEvent(event))
		{
			//Check if the event was to close the window
			if (event.type == sf::Event::Closed)
			{
				//Close the application
				window.close();
			}
		}
		//Check for input and autoplay features
		AutoPlayAndInput();
		//Check for collisions of the paddles and ball
		Collisions();
		//Allow the game to be paused by hitting the space bar if the game is a debug build.
		DebugPause();
	}
}
