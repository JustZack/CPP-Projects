#pragma once
struct Domain
{
public:
	float xMin, xMax, yMin, yMax;
	Domain() {}
	Domain(float XMin, float XMax, float YMin, float YMax)
	{
		xMin = XMin;
		xMax = XMax;
		yMin = YMin;
		yMax = YMax;
	}
};