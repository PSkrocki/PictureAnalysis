#include "PlyFilesManager.h"


PlyFilesManager::PlyFilesManager(){

}


PlyFilesManager::~PlyFilesManager(){

}

string PlyFilesManager::getPathToCompressedFile(){
	return pathToCompressedFile;
}

vector<Point*> PlyFilesManager::getSelectionPoints(){
	return selectionPoints;
}
