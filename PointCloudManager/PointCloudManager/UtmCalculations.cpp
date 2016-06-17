#include "utmcalculations.h"
#include "utmpoint.h"
#include "utmpoint.h"
#include <iostream>
#include "Point.h"


UtmCalculations::UtmCalculations()
{

}

bool UtmCalculations::downCompare(UTMPoint point1, UTMPoint point2)
{

	if (point1.Hemisphere < point2.Hemisphere)
	{
		return true;
	}
	else
	{
		if (point1.Hemisphere == point2.Hemisphere)
		{
			return (point1.Northing < point2.Northing);
		}
		else
		{
			return false;
		}

	}
}

bool UtmCalculations::leftCompare(UTMPoint point1, UTMPoint point2)
{

	if (point1.Zone < point2.Zone)
	{
		return true;
	}
	else
	{
		if (point1.Zone == point2.Zone)
		{
			return (point1.Easting < point2.Easting);
		}
		else
		{	
			return false;
		}
	}
}

void UtmCalculations::offset(vector<Point> &utmPoints, UTMPoint leftPoint, UTMPoint downPoint)
{
	for (unsigned int i = 0; i<utmPoints.size(); i++)
	{
		utmPoints[i].x -= leftPoint.Easting;
		utmPoints[i].y -= downPoint.Northing;  
	}
}


UTMPoint UtmCalculations::LLtoUTM(double Lat, double Long, double& Northing, double& Easting, int& Zone)
{
	long double a = 6378137;

	double fr = 298.257223563;

	long double ee = 2 / fr - 1 / (fr*fr);
	Long -= int((Long + 180) / 360) * 360;			//ensure longitude within -180.00..179.9
	double N, T, C, A, M;
	double LatRad = Lat*deg2rad;
	double LongRad = Long*deg2rad;

	Zone = int((Long + 186) / 6);
	if (Lat >= 56.0 && Lat < 64.0 && Long >= 3.0 && Long < 12.0)  Zone = 32;
	if (Lat >= 72.0 && Lat < 84.0) {			//Special zones for Svalbard
		if (Long >= 0.0  && Long <  9.0)  Zone = 31;
		else if (Long >= 9.0  && Long < 21.0)  Zone = 33;
		else if (Long >= 21.0 && Long < 33.0)  Zone = 35;
		else if (Long >= 33.0 && Long < 42.0)  Zone = 37;
	}
	double LongOrigin = Zone * 6 - 183;			//origin in middle of zone
	double LongOriginRad = LongOrigin * deg2rad;

	double EE = ee / (1 - ee);

	N = a / sqrt(1 - ee*sin(LatRad)*sin(LatRad));
	T = tan(LatRad)*tan(LatRad);
	C = EE*cos(LatRad)*cos(LatRad);
	A = cos(LatRad)*(LongRad - LongOriginRad);

	M = a*((1 - ee / 4 - 3 * ee*ee / 64 - 5 * ee*ee*ee / 256) *LatRad
		- (3 * ee / 8 + 3 * ee*ee / 32 + 45 * ee*ee*ee / 1024) *sin(2 * LatRad)
		+ (15 * ee*ee / 256 + 45 * ee*ee*ee / 1024) *sin(4 * LatRad)
		- (35 * ee*ee*ee / 3072) *sin(6 * LatRad));

	Easting = k0*N*(A + (1 - T + C)*A*A*A / 6 + (5 - 18 * T + T*T + 72 * C - 58 * EE)*A*A*A*A*A / 120) + 500000.0;

	Northing = k0*(M + N*tan(LatRad)*(A*A / 2 + (5 - T + 9 * C + 4 * C*C)*A*A*A*A / 24
		+ (61 - 58 * T + T*T + 600 * C - 330 * EE)*A*A*A*A*A*A / 720));


	char x = Northing < 0 ? 'S' : 'N';

	if (N<0) N += 10000000;

	UTMPoint point(Northing, Easting, Zone, x);

	return point;
}

vector<Point> UtmCalculations::Convert(vector<Point> LLPoints)
{
	double x, y;
	int z;

	UTMPoint LeftmostUtmPoint = LLtoUTM(LLPoints[0].y, LLPoints[0].x,x,y,z);
	UTMPoint LowermostUtmPoint = LeftmostUtmPoint;

	vector <Point> result;
	
	cout << "UTM\n";

	for (int i = 0; i<LLPoints.size(); i++)
	{
		

		UTMPoint temp = LLtoUTM(LLPoints[i].y, LLPoints[i].x,x,y,z);		
		result.push_back(Point(temp.Easting, temp.Northing, LLPoints[i].z, 0));
		
		if (UtmCalculations::downCompare(temp, LowermostUtmPoint))
		{
			LowermostUtmPoint = temp;
		}

		if (UtmCalculations::leftCompare(temp, LowermostUtmPoint))
		{
			LeftmostUtmPoint = temp;
		}
	}

	//offset(result, LeftmostUtmPoint, LowermostUtmPoint);

	return result;
}




