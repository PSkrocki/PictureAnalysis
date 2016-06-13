#ifndef ORIGINALSELECTION_H
#define ORIGINALSELECTION_H
#include "vector"
#include "stdlib.h"
#include "string"
#include "rply.h"
#include "Point.h"
using namespace std;

class OriginalSelection
{
public:
	OriginalSelection();


	vector<Point> GetOriginalSelection(char *pathToFile, vector<size_t> selectedIndexes);

private:

	vector<Point> checkPoints(vector<size_t> index);
	static int IsInPolygin(int nvert, vector<double> vertx, vector<double> verty, double testx, double testy);
	void readPlyFile(char *path);

	static vector<vector<double> > points;	
	static int GetVertex(p_ply_argument argument);
	static int currentIndex;
	static int count;

};

#endif // ORIGINALSELECTION_H
