#pragma once
/*
	File compression mode:
		Gets: Path to file to compress in string, compression percentage in int
		Returns: Path to compressed file in string
	Retriving selection mode:
		Gets: List of points indexes in size_t, path to original compressed file 
		Returns: List of points.
				 Those points are bare from GPS system, it's full selection (including points
				 that were cut off for rendering purposes)
*/

#include "Point.h"
#include <string>
#include <vector>

using namespace std;

class PlyFilesManager
{
private:
	string pathToCompressedFile;
	vector<Point*> selectionPoints;
public:
	PlyFilesManager();
	~PlyFilesManager();
	string getPathToCompressedFile();
	vector<Point*> getSelectionPoints();
};

