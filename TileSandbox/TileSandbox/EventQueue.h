#pragma once
#include <vector>
#include "states.h"

enum eType
{
	MOVE_UP, //Start of a MOVE
	MOVE_UP_RIGHT,
	MOVE_RIGHT,
	MOVE_DOWN_RIGHT,
	MOVE_DOWN,
	MOVE_DOWN_LEFT,
	MOVE_LEFT,
	MOVE_UP_LEFT, // End of a MOVE
	ZOOM_IN, //Start of a ZOOM
	ZOOM_OUT,//End of a ZOOM
	CLICK, //Start of a MOUSE
	MOUSE_ENTER,
	MOUSE_LEAVE,
	HOVER,
	PLACE, //End of a MOUSE
	NONE
};
enum eBase
{
	bMOVE,
	bZOOM,
	bMOUSE,
	bNONE
};

struct eInfo
{
	//type of event / action
	eType type;
	eBase baseType;
	//Tile location that *may* be affecteed
	int coordX, coordY;
	//New possible PrimaryState
	PrimaryState pState;
	//New possible seconaryState
	SecondaryState sState;
	void init();
	eInfo();
	eInfo(const eInfo& eventInfo);
	eInfo(eType Type);
	eInfo(eType Type, int xCoord, int yCoord);
	eInfo(eType Type, int xCoord, int yCoord, PrimaryState PState);
	eInfo(eType Type, int xCoord, int yCoord, SecondaryState SState);
	eInfo(eType Type, int xCoord, int yCoord, PrimaryState PState, SecondaryState SState);
};

/* http://gameprogrammingpatterns.com/event-queue.html */
class EventQueue
{
public: static const int EVENT_COUNT = 3;
private:
	std::vector<eInfo> eventQueue;
	eInfo _eventQueue [EVENT_COUNT];
	eInfo temp;

	//TODO: Could have different vectors for different types of events
	//Movement, sound, placment of tiles, etc
public:
	//Default constructor 
	EventQueue();
	//Add an event to the event list.
	void add(eInfo eventInfo);
	//Get the next event
	eInfo next();
};