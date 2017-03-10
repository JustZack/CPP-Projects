#include "EventQueue.h"

EventQueue::EventQueue()
{

}
//Add a new event to the end of the event queue
void EventQueue::add(eInfo eventInfo)
{
	switch (eventInfo.baseType)
	{
		case bMOVE:
			_eventQueue[0] = eventInfo;
			break;
		case bZOOM:
			_eventQueue[1] = eventInfo;
			break;
		case bMOUSE:
			_eventQueue[2] = eventInfo;
			break;
	}
}
//Get the next event to be processed
eInfo EventQueue::next()
{
	temp = _eventQueue[0];
	for (int i = 0; i < EVENT_COUNT - 1; i++)
		_eventQueue[i] = _eventQueue[i + 1];
	_eventQueue[EVENT_COUNT - 1] = eInfo(eType::NONE);
	return temp;
}

void eInfo::init()
{
	if (type >= MOVE_UP && type <= MOVE_UP_LEFT)
		baseType = bMOVE;
	if (type >= ZOOM_IN && type <= ZOOM_OUT)
		baseType = bZOOM;
	if (type >= CLICK && type <= PLACE)
		baseType = bMOUSE;
}
//Defualt constructor
eInfo::eInfo()
{
	init();
}

eInfo::eInfo(const eInfo& eventInfo)
{
	type = eventInfo.type;
	coordX = eventInfo.coordX;
	coordY = eventInfo.coordY;
	pState = eventInfo.pState;
	sState = eventInfo.sState;
	init();
}

eInfo::eInfo(eType Type)
{
	type = Type;
	init();
}
eInfo::eInfo(eType Type, int xCoord, int yCoord)
{
	type = Type;
	coordX = xCoord;
	coordY = yCoord;
	init();
}
eInfo::eInfo(eType Type, int xCoord, int yCoord, PrimaryState PState)
{
	type = Type;
	coordX = xCoord;
	coordY = yCoord;
	pState = PState;
	init();
}
eInfo::eInfo(eType Type, int xCoord, int yCoord, SecondaryState SState)
{
	type = Type;
	coordX = xCoord;
	coordY = yCoord;
	sState = SState;
	init();
}

eInfo::eInfo(eType Type, int xCoord, int yCoord, PrimaryState PState, SecondaryState SState)
{
	type = Type;
	coordX = xCoord;
	coordY = yCoord;
	pState = PState;
	sState = SState;
	init();
}