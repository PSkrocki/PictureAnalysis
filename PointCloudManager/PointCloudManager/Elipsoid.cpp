#include "Elipsoid.h"

Ellipsoid::Ellipsoid(int id, std::string name, double radius, double fr)
{
	Name = name;  EquatorialRadius = radius;  eccSquared = 2 / fr - 1 / (fr*fr);
}
