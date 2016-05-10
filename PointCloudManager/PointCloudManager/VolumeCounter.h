#pragma once
/*
	Gets: List of points.
		  Those points are in UTM system
	Returns: Given point cloud's volume in double, counted error in double
*/

#include "Point.h"

class VolumeCounter
{
private:
	double volume;
	double error;

public:
	VolumeCounter();
	~VolumeCounter();
	double getVolume();
	double getError();
};

