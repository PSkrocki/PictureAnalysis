#include "RestManager.h"
#include <cpprest\json.h>
#include <cpprest\http_client.h>
#include <Windows.h>
#include <sstream>

using namespace std;
using namespace web;
using namespace web::http;
using namespace web::http::client;


RestManager::RestManager(){
}


RestManager::~RestManager(){

}

void RestManager::setFilesJson(string dirPath){
	json::value clear;
	filesJson = clear;
	//TODO - get all ply files from given directory
}

json::value RestManager::getFilesJson(){
	return filesJson;
}

void RestManager::setChosenFileAndCompression(string filePath, string compression){
	chosenFileJson[L"chosen"] = json::value::string(wstring(filePath.begin(), filePath.end()));
	chosenFileJson[L"compression"] = json::value::string(wstring(compression.begin(), compression.end()));
}

void RestManager::setCompressedFile(string filePath){
	chosenFileJson[L"compressedFile"] = json::value::string(wstring(filePath.begin(), filePath.end()));
}

json::value RestManager::getChosenFileJson(){
	return chosenFileJson;
}

void RestManager::setSelection(){
	//TODO - add parameter and fill
}

json::value RestManager::getSelection(){
	return selectionJson;
}

void RestManager::setValues(vector<double> values){
	string buf;
	ostringstream stream;
	stream << values[0];
	buf = stream.str();
	stream.clear();
	valuesJson[L"volume"] = json::value::string(wstring(buf.begin(), buf.end()));
	stream << values[1];
	buf = stream.str();
	stream.clear();
	valuesJson[L"error"] = json::value::string(wstring(buf.begin(), buf.end()));
}

json::value RestManager::getValues(){
	return valuesJson;
}