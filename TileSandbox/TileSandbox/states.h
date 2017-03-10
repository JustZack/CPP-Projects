#pragma once

//The Primary state is what everything else must exist on top of, and can be seen.
//Like Flooring, or dirt / grass. But not a table or bush.
enum PrimaryState 
{
	EMPTY,
	FLOORED,
	CLICKED,
	ERROR
};
//A structure ontop of the base State.
//Like a table, door, chair, 
enum SecondaryState
{

};