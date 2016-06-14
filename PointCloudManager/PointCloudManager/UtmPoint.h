#ifndef UTMPOINT_H
#define UTMPOINT_H

#include "string"

using namespace std;

class UTMPoint
{
public:
	UTMPoint(double North, double East, int Zone, char Hemisphere);
	string Print();

	double Northing;
	double Easting;
	int Zone;
	char Hemisphere;
};

#endif // UTMPOINT_H
