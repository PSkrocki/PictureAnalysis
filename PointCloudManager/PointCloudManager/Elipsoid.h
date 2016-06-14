#include "string"

class Ellipsoid
{
public:
	Ellipsoid(int id, std::string name, double radius, double fr);

	std::string Name;
	double EquatorialRadius;
	double eccSquared;
};


