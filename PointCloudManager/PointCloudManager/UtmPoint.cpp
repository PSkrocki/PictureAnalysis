#include "utmpoint.h"
#include "string"
using namespace std;

UTMPoint::UTMPoint(double North, double East, int Zone, char Hemisphere)
{
	Northing = North;
	Easting = East;
	this->Zone = Zone;
	this->Hemisphere = Hemisphere;
}

string UTMPoint::Print()
{
	return "NORT " + std::to_string(Northing) + " EAST " + std::to_string(Easting) + " " + std::to_string(Zone) + Hemisphere + "\n";
}
