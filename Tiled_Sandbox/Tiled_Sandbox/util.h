#pragma once
enum States
{
	Empty,
	Floored
};
class intPair
{
	private:
		int x, y;
	public:
		intPair();
		intPair(int X, int Y);
		int X();
		int Y();
};
class floatPair
{
private:
	float x, y;
public:
	floatPair();
	floatPair(int X, int Y);
	float X();
	float Y();
};