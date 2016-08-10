#pragma once
#include "Object.h"

class DynamicObject : public Object 
{
public:
	DynamicObject() : Object() {};
	DynamicObject(float X, float Y, float Mass, float Width, float Height) : Object(X, Y, Mass, Width, Height) 
	{
		//TODO: Learn more about inheratence
		isAffectedByGravity(true);
		isMoveable(true);
		hasCollision(true);
	};
};
class StaticObject : public Object
{
public:
	StaticObject() : Object() {};
	StaticObject(float X, float Y, float Mass, float Width, float Height) : Object(X, Y, Mass, Width, Height)
	{
		//TODO: Learn more about inheratence
		isAffectedByGravity(false);
		isMoveable(false);
		hasCollision(true);
	};
};