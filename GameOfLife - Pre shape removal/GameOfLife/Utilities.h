#pragma once

struct Point
{
	float x, y;
	Point()
	{
		x = 0;
		y = 0;
	}
	Point(float X, float Y)
	{
		x = X;
		y = Y;
	}
};

struct Size
{
	int Width, Height;
	Size()
	{
		Width = 0;
		Height = 0;
	}
	Size(int width, int height)
	{
		Width = width;
		Height = height;
	}

};

enum State
{
	Dead,
	Alive
};