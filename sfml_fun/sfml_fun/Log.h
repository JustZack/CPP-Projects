#pragma once

#include <iostream>


//Used to determine if messages are allowed to show up
#define DEBUG 1      //Displays on hit notifications, rounds wins, and score increases
					 //Also allows the players to pause the game with the space bar

#define DEBUG_FULL 0 //Displays the above plus every time any object on screen is moved 
					 //a message displays its new location
#if DEBUG
	//Logs simple things
	#define Log(x) std::cout << x << std::endl;
	//Checks if the debug full variable is also one
	#if DEBUG_FULL
	//Logs everything
	#define Log_Fast(x) std::cout << x << std::endl;
	#else
	//Logs nothing fast
	#define Log_Fast(x);
	#endif
#else
#define Log(x)
#define Log_Fast(x)
#endif
