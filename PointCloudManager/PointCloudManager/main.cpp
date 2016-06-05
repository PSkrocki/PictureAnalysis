#include <iostream>

#include <process.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "ServerSetup.h"

using namespace std;

RestManager* restManager;

int main()
{
	cout << "Point Cloud Manager" << endl;
	restManager = new RestManager();
	init(restManager);
	getchar();



}