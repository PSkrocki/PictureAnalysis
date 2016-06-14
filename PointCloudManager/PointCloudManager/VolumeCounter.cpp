#include "VolumeCounter.h"
#include <iostream>
#include <cstdio>
#include <vector>
#include <fstream>

#define NUMBER_TRIALS 1 
#define TETLIBRARY


using namespace std;


VolumeCounter::VolumeCounter() {
	cout << "sdfsdf" << endl;
	run_test();
}


struct VolumeCounter::Tetrahedron
{
	Point p1;
	Point p2;
	Point p3;
	Point p4;
};

struct VolumeCounter::VolumeArray {
	double array[5][5];
};

struct VolumeCounter::PointsArray {
	double array[8];
	int sizeOfArray() {
		return sizeof(array);
	}
};

double VolumeCounter::distanceBetweenPoints(Point p1, Point p2) {
	return sqrt(pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2) + pow((p1.z - p2.z), 2));
}

VolumeCounter::VolumeArray VolumeCounter::fillArray(Tetrahedron tet) {

	double volumeArray[5][5] = {
		{ 0,	pow(distanceBetweenPoints(tet.p1 , tet.p2),2),		pow(distanceBetweenPoints(tet.p1 , tet.p3),2),		pow(distanceBetweenPoints(tet.p1 , tet.p4),2),		1 },
		{ pow(distanceBetweenPoints(tet.p1 , tet.p2),2),	0,		pow(distanceBetweenPoints(tet.p2 , tet.p3),2),		pow(distanceBetweenPoints(tet.p2 , tet.p4),2),		1 },
		{ pow(distanceBetweenPoints(tet.p1 , tet.p3),2),	pow(distanceBetweenPoints(tet.p2 , tet.p3),2),		0,		pow(distanceBetweenPoints(tet.p3 , tet.p4),2),		1 },
		{ pow(distanceBetweenPoints(tet.p1 , tet.p4),2),	pow(distanceBetweenPoints(tet.p2 , tet.p4),2),		pow(distanceBetweenPoints(tet.p3 , tet.p4),2),		0,		1 },
		{ 1,1,1,1,0 }
	};

	VolumeArray singleArray;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			singleArray.array[i][j] = volumeArray[i][j];
		}
	}
	return singleArray;
}

double VolumeCounter::determinant(VolumeCounter::VolumeArray volumeArray, int n) {
	double a[5][5];
	for (int d = 0; d < 5; d++) {
		for (int e = 0; e < 5; e++) {
			a[d][e] = volumeArray.array[d][e];
		}
	}
	int p, h, k, i, j;
	VolumeArray temp;
	double det = 0;
	if (n == 1) {
		return a[0][0];
	}
	else if (n == 2) {
		det = (a[0][0] * a[1][1] - a[0][1] * a[1][0]);
		return det;
	}
	else {
		for (p = 0; p<n; p++) {
			h = 0;
			k = 0;
			for (i = 1; i<n; i++) {
				for (j = 0; j<n; j++) {
					if (j == p) {
						continue;
					}
					temp.array[h][k] = a[i][j];
					k++;
					if (k == n - 1) {
						h++;
						k = 0;
					}
				}
			}
			det = det + a[0][p] * pow(-1, p)*determinant(temp, n - 1);
		}
		return det;
	}
}

double VolumeCounter::calculateVolume(double determinant) {

	double fraction = determinant / 288;
	return sqrt(abs(fraction));
}


void VolumeCounter::saveToFile(string path, vector <Point> pointsArray, int howManyInputs, int numberOfPoints, int howManyEdges) {
	ofstream NowyPlik;
	NowyPlik.open(path);


	NowyPlik << "ply" << endl;
	NowyPlik << "format ascii 1.0" << endl;
	NowyPlik << "element vertex " << numberOfPoints << endl;
	NowyPlik << "property float32 x" << endl;
	NowyPlik << "property float32 y" << endl;
	NowyPlik << "property float32 z" << endl;
	NowyPlik << "element edge " << howManyEdges << endl;
	NowyPlik << "property int vertex1" << endl;
	NowyPlik << "property int vertex2" << endl;
	NowyPlik << "property list uint8 int32 vertex_indices" << endl;
	NowyPlik << "end_header" << endl;
	for (int i = 0; i < howManyInputs; i++) {
		if (i < numberOfPoints) {
			NowyPlik << pointsArray[i].x << " " << pointsArray[i].y << endl;
		}
		else {
			NowyPlik << pointsArray[i].x << " " << pointsArray[i].y << endl;
		}
	}
	NowyPlik.close();
}
/*
vector<Point> getPointsFromFile(string filePath) {

vector<Point> vectorOfPoints;
double a, b, c;
int m, n, o;
int numberOfPoints;
Point point;
int tmp = 0;
int i = 0;
ifstream points(filePath);

if (!points)
{
cout << "Nie mozna otworzyc pliku";
getchar();
return vectorOfPoints;
}

while (!points.eof()) {
points >> a >> b >> c >> m >> n >> o;
point.x = a;
point.y = b;
point.z = c;
vectorOfPoints.push_back(point);
tmp++;
}

points.close();
fstream plik("wczytanePunkty.txt", ios::out);
if (plik.good()) {
for (int i = 0; i < vectorOfPoints.size(); i++) {
//cout << vectorOfPoints.at(i).x << endl;
//cout << vectorOfPoints.at(i).y << endl;
//cout << vectorOfPoints.at(i).z << endl;
plik << vectorOfPoints.at(i).x << vectorOfPoints.at(i).y << vectorOfPoints.at(i).z << endl;
plik.flush();
}
}

return vectorOfPoints;

}
*/


double  VolumeCounter::run_test()
{
	double volume = 0;
	int n;
	tetgenio inp, out;

	inp.initialize();
	out.initialize();

	Point pkt1(0.2, 0.0, 0.1, 0);
	Point pkt2(0.5, 0.1, 0.0, 0);
	Point pkt3(0.8, 0.2, 0.0, 0);
	Point pkt4(1.7, 0.5, 0.2, 0);
	Point pkt5(2.2, 0.4, 0.0, 0);
	Point pkt6(0.7, 0.6, 0.3, 0);
	Point pkt7(0.9, 1.0, 0.2, 0);
	Point pkt8(2.0, 0.8, 0.3, 0);
	Point pkt9(0.3, 1.4, 0.3, 0);
	Point pkt10(0.6, 1.3, 0.3, 0);
	Point pkt11(1.5, 1.7, 0.5, 0);
	Point pkt12(0.4, 1.8, 0.5, 0);
	Point pkt13(1.0, 2.0, 0.8, 0);


	int indexesOfEdgePoint[10];
	indexesOfEdgePoint[0] = 0;
	indexesOfEdgePoint[1] = 1;
	indexesOfEdgePoint[2] = 2;
	indexesOfEdgePoint[3] = 3;
	indexesOfEdgePoint[4] = 4;
	indexesOfEdgePoint[5] = 7;
	indexesOfEdgePoint[6] = 10;
	indexesOfEdgePoint[7] = 12;
	indexesOfEdgePoint[8] = 11;
	indexesOfEdgePoint[9] = 8;

	vector <Point> pointsVector;
	//= getPointsFromFile("output_2_ASCII.ply");

	pointsVector.push_back(pkt1);
	pointsVector.push_back(pkt2);
	pointsVector.push_back(pkt3);
	pointsVector.push_back(pkt4);
	pointsVector.push_back(pkt5);
	pointsVector.push_back(pkt6);
	pointsVector.push_back(pkt7);
	pointsVector.push_back(pkt8);
	pointsVector.push_back(pkt9);
	pointsVector.push_back(pkt10);
	pointsVector.push_back(pkt11);
	pointsVector.push_back(pkt12);
	pointsVector.push_back(pkt13);

	///DODANIE ZRZUTOWANYCH PUNKTOW KRANCOWYCH


	for (int i = 0; i < (sizeof(indexesOfEdgePoint) / sizeof(*indexesOfEdgePoint)); i++) {

		int j = indexesOfEdgePoint[i];
		Point point(pointsVector[j].x, 0, pointsVector[j].z, 0);
		pointsVector.push_back(point);
	}



	inp.numberofpoints = pointsVector.size();
	inp.pointlist = new REAL[inp.numberofpoints * 3];

	for (int n = 0; n < pointsVector.size(); n++) {

		inp.pointlist[3 * n + 0] = pointsVector[n].x;
		inp.pointlist[3 * n + 1] = pointsVector[n].y;
		inp.pointlist[3 * n + 2] = pointsVector[n].z;
	}


	tetrahedralize("veeQ", &inp, &out);


	//cout << "faces:" << endl;
	for (int i = 0; i < out.numberoftrifaces; i++) {
		//cout << "face:" << endl;
		//cout << out.trifacelist[i * 3 + 0] << " ";
		//cout << out.trifacelist[i * 3 + 1] << " ";
		//cout << out.trifacelist[i * 3 + 2] << endl;
	}

	vector <Tetrahedron> tetrahedronsVector;

	//cout << "tetra:" << endl;
	for (int i = 0; i < out.numberoftetrahedra; i++) {

		Tetrahedron tetrahedron =
		{
			pointsVector[out.tetrahedronlist[i * 4 + 0]],
			pointsVector[out.tetrahedronlist[i * 4 + 1]],
			pointsVector[out.tetrahedronlist[i * 4 + 2]],
			pointsVector[out.tetrahedronlist[i * 4 + 3]]
		};
		//cout << out.tetrahedronlist[i * 4 + 0] << " ";
		//cout << out.tetrahedronlist[i * 4 + 1] << " ";
		//cout << out.tetrahedronlist[i * 4 + 2] << " ";
		//cout << out.tetrahedronlist[i * 4 + 4] << " " << endl << endl;

		//DODANIE CZWOROSCIANOW DO TABLICY 

		//tetrahedron.p1 = pointsVector[out.tetrahedronlist[i * 4 + 0]];
		//tetrahedron.p2 = pointsVector[out.tetrahedronlist[i * 4 + 1]];
		//tetrahedron.p3 = pointsVector[out.tetrahedronlist[i * 4 + 2]];
		//tetrahedron.p4 = pointsVector[out.tetrahedronlist[i * 4 + 3]];

		tetrahedronsVector.push_back(tetrahedron);
	}


	//WYPELNIENIE MACIERZY DO LICZENIA WYZNACZNIKOW, WSZYSTKIE MACIERZE ZNAJDUJA SIE W VECTORZE tetrahedronsArrayVector

	vector <VolumeArray> tetrahedronsArrayVector;

	for (int i = 0; i < tetrahedronsVector.size(); i++) {

		tetrahedronsArrayVector.push_back(fillArray(tetrahedronsVector[i]));
	}

	cout << "ile czworoscianow w tablicy?" << tetrahedronsVector.size();

	cout << "Delaunay information:" << endl;
	cout << "numberofpoints: " << out.numberofpoints << endl;
	cout << "numberofedges: " << out.numberofedges << endl;
	cout << "numberoftrifaces: " << out.numberoftrifaces << endl;
	cout << "numberoftetrahedra: " << out.numberoftetrahedra << endl;
	cout << "numberofcorners: " << out.numberofcorners << endl;

	determinant(tetrahedronsArrayVector.at(1), 5);

	fstream plik("plik.txt", ios::out);
	if (plik.good()) {
		for (int i = 0; i < tetrahedronsVector.size(); i++) {

			plik << "Volume of " << i + 1 << " tetrahedron = " << calculateVolume(determinant(tetrahedronsArrayVector.at(i), 5)) << endl;
			plik.flush();


			//cout << "Volume of " << i + 1 << " tetrahedron = " << calculateVolume(determinant(tetrahedronsArrayVector.at(i), 5)) << endl;
			volume += calculateVolume(determinant(tetrahedronsArrayVector.at(i), 5));
		}
		plik.close();
	}
	cout << "Volume of surface = " << volume << endl;



	for (int n = 0; n<out.numberoftrifaces; ++n) {
		int n0 = out.trifacelist[3 * n + 0];
		int n1 = out.trifacelist[3 * n + 1];
		int n2 = out.trifacelist[3 * n + 2];

		REAL *u = &out.pointlist[3 * n0];
		REAL *v = &out.pointlist[3 * n1];
		REAL *y = &out.pointlist[3 * n2];
		//printf("(%f %f %f) -> (%f %f %f) -> (%f %f %f)\n", u[0], u[1], u[2], v[0], v[1], v[2], y[0], y[1], y[2]);
	}

	vector<Point> pointsArray;
	for (int n = 0; n < out.numberofpoints; n++) {
		REAL *u = &out.pointlist[3 * n];
		//printf("(%f %f %f)\n", u[0], u[1], u[2]);

		Point point(u[0], u[1], u[2], 0);
		pointsArray.push_back(point);

	}

	for (int i = 0; i < out.numberofedges; i++) {
		Point point(out.edgelist[i * 2 + 0], out.edgelist[i * 2 + 0], 0, 0);
		pointsArray.push_back(point);
	}

	saveToFile("test.ply", pointsArray, pointsArray.size(), out.numberofpoints, out.numberofedges);


	//out.save_edges("esgesFile");
	//out.save_elements("elementsFile");
	//out.save_poly("polyFule");
	//out.save_faces2smesh("faces2smesh");
	//out.save_faces("faces");

	return volume;
}