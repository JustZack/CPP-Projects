#include "util.h"

//intPair class declairation in the util header file.
intPair::intPair()
{
	x = 0;
	y = 0;
}
intPair::intPair(int X, int Y)
{
	x = X;
	y = Y;
}
int intPair::X()
{
	return x;
}
int intPair::Y()
{
	return y;
}

//floatPair class declairation in the util header file.
floatPair::floatPair()
{
	x = 0;
	y = 0;
}
floatPair::floatPair(int X, int Y)
{
	x = X;
	y = Y;
}
float floatPair::X()
{
	return x;
}
float floatPair::Y()
{
	return y;
}