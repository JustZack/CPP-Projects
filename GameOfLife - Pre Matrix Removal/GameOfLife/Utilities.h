#pragma once

//Array size can go up to 204 with 1MB of stack memory
//Not sure of new max whith 100MB of stack memory
	//Atleast 2000
#define ARRAY_SIZE 100
#define INITIAL_POP 2500

enum State
{
	Dead,
	Alive
};