#include "originalselection.h"
#include "stdlib.h"
#include "rply.h"
#include "ctime"
#include "iostream"

using namespace std;

int OriginalSelection::currentIndex;
int OriginalSelection::count;

vector<vector<double> > OriginalSelection::data;

OriginalSelection::OriginalSelection()
{

}

int OriginalSelection::pnpoly(int nvert, vector<double> vertx, vector<double> verty, double testx, double testy)
{
	int i, j, c = 0;

	for (i = 0, j = nvert - 1; i < nvert; j = i++)
	{
		if (((verty[i]>testy) != (verty[j]>testy)) &&
			(testx < (vertx[j] - vertx[i]) * (testy - verty[i]) / (verty[j] - verty[i]) + vertx[i]))
			c = !c;
	}
	return c;
}

int OriginalSelection::vertex_cb(p_ply_argument argument) {
	long eol;

	ply_get_argument_user_data(argument, NULL, &eol);

	data[currentIndex].push_back(ply_get_argument_value(argument));

	if (eol)
	{
		currentIndex++;
	}

	return 1;
}


int OriginalSelection::readPlyFile(char *path, vector<size_t> indexForCheck, vector< vector<double> > &result)
{
	size_t nvertices;

	currentIndex = 0;

	cout << "starting reading \n";
	p_ply ply = ply_open(path, NULL, 0, NULL);
	//p_ply ply = ply_open("example.ply", NULL, 0, NULL);
	if (!ply) return 1;
	if (!ply_read_header(ply)) 1;
	nvertices = ply_set_read_cb(ply, "vertex", "x", reinterpret_cast<p_ply_read_cb>(&vertex_cb), NULL, 0);
	ply_set_read_cb(ply, "vertex", "y", reinterpret_cast<p_ply_read_cb>(&vertex_cb), NULL, 0);
	ply_set_read_cb(ply, "vertex", "z", reinterpret_cast<p_ply_read_cb>(&vertex_cb), NULL, 1);

	data.reserve(nvertices);

	cout << "points: " << nvertices << endl;

	if (!ply_read(ply)) return 1;

	cout << "data size:" << data.capacity() << endl;

	ply_close(ply);

	result = checkPoints(indexForCheck, data);
}

vector<vector<double> > OriginalSelection::checkPoints(vector<size_t> index, vector<vector<double> > points)
{
	vector<double> polyX, polyY;

	vector< vector<double> > result;

	for (size_t i = 0; i < index.size(); i++)
	{
		polyX.push_back(points[index[i]][0]);
		polyY.push_back(points[index[i]][1]);
	}

	double xMin = polyX[0],
		xMax = polyX[0],
		yMin = polyY[0],
		yMax = polyY[0];

	for (size_t i = 0; i<polyX.size(); i++)
	{
		if (polyX[i] > xMax)
		{
			xMax = polyX[i];
		}
		if (polyX[i] < xMin)
		{
			xMin = polyX[i];
		}
		if (polyY[i] > yMax)
		{
			yMax = polyY[i];
		}
		if (polyY[i] < yMax)
		{
			yMin = polyY[i];
		}
	}

	for (size_t i = 0; i<data.size(); i++)
	{
		if (data[i][0] < xMin)
			continue;

		if (data[i][0] > xMax)
			continue;

		if (data[i][1] < yMin)
			continue;

		if (data[i][1] > yMax)
			continue;

		int w = pnpoly(index.size(), polyX, polyY, data[i][0], data[i][1]);

		if (w == 1)
		{
			result.push_back(data[i]);
		}
	}

	return result;
}


