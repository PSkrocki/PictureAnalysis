#ifndef ORIGINALSELECTION_H
#define ORIGINALSELECTION_H
#include "vector"
#include "stdlib.h"
#include "string"
#include "rply.h"
using namespace std;

class OriginalSelection
{
public:
	OriginalSelection();

	static int pnpoly(int nvert, vector<double> vertx, vector<double> verty, double testx, double testy);

	int readPlyFile(char *path, vector<size_t> indexForCheck, vector< vector<double> > &result);

	static void staticVOid();

	static vector<vector<double> > data;

	static vector<vector<double> > checkPoints(vector<size_t> index, vector<vector<double> > points);

	static int vertex_cb(p_ply_argument argument);

	static int currentIndex;

	static int count;

};

#endif // ORIGINALSELECTION_H
