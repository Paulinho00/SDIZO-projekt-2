#include "Graphs.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
using namespace std;

GraphMatrix::GraphMatrix(bool isDirected){
	weightMatrix = nullptr;
	this->isDirected = isDirected;
}

GraphMatrix::~GraphMatrix() {
	dropGraph();
}

//Losowe generowanie grafu
void GraphMatrix::generateGraph(int vertices, float density) { 
	if (weightMatrix != nullptr) dropGraph();
	allocateArray(vertices);

	int maxNumberOfEdges = (vertices * (vertices - 1)) / 2;
	int desiredNumberOfEdges = maxNumberOfEdges * density;

	//Sprawdzenie czy mo�na utworzy� graf rozpinaj�cy przy danej g�sto�ci
	if (desiredNumberOfEdges < (vertices - 1)) {
		cout << "Gestosc jest za niska dla tej liczby wierzcholkow (nie mozna utworzyc grafu rozpinajacego)\n";
		return;
	}
	
	//Generowanie drzewa rozpinaj�cego
	srand(time(NULL));
	int randomWeight = rand()%20 + 1;
	int vertex;
	addEdge(0, 1, randomWeight);
	int i = 2;
	while(i < numberOfVertices) {
		randomWeight = rand() % 20 + 1;
		vertex = rand() % i;
		if (vertex != i && weightMatrix[i][vertex] == INT_MIN) {
			addEdge(i, vertex, randomWeight);
			i++;
		}
		else continue;

	}

	//Generowanie dodatkowych kraw�dzi, aby osiagnac odpowiednia gestosc
	while (numberOfEdges < desiredNumberOfEdges) {
		int firstVertexToEdge = rand() % numberOfVertices;
		int secondVertexToEdge = rand() % numberOfVertices;
		randomWeight = rand() % 20 + 1;
		if (firstVertexToEdge != secondVertexToEdge && weightMatrix[firstVertexToEdge][secondVertexToEdge] == INT_MIN) {
			addEdge(firstVertexToEdge, secondVertexToEdge, randomWeight);
		}
	}

}

//Wy�wietlenie grafu w odpowiedniej reprezentacji
void GraphMatrix::showGraph() {
	cout << "\n    |";
	for (int i = 0; i < numberOfVertices; i++) printf("  %3d", i);
	cout << "\n";
	for (int i = 0; i < numberOfVertices; i++) {
		printf("\n%3d |", i);
		for (int j = 0; j < numberOfVertices; j++) {
			if (weightMatrix[i][j] != INT_MIN) printf("  %3d", weightMatrix[i][j]);
			else  printf("  %3d", 0);
		}
		cout << "|";
	}
}

//Usuwa graf
void GraphMatrix::dropGraph() {
	for (int i = 0; i < numberOfVertices; i++) {
		delete weightMatrix[i];
	}
	delete weightMatrix;
	weightMatrix = nullptr;
	numberOfEdges = 0;
	numberOfVertices = 0;
}

//Dodaje kraw�d� grafu
void GraphMatrix::addEdge(int firstVertex, int secondVertex, int weight) {
		weightMatrix[firstVertex][secondVertex] = weight;
		if (!isDirected) {
			weightMatrix[secondVertex][firstVertex] = weight;
		}
		numberOfEdges++;
}

void GraphMatrix::allocateArray(int numberOfVertices) {
	this->numberOfVertices = numberOfVertices;
	weightMatrix = new int* [numberOfVertices];
	for (int i = 0; i < numberOfVertices; i++) {
		weightMatrix[i] = new int[numberOfVertices];

		//Wypelnienie macierzy warto�ciami -inf oznaczaj�cymi brak po��czenia
		for (int j = 0; j < numberOfVertices; j++) {
			weightMatrix[i][j] = INT_MIN;
		}
	}
}

//Wyznaczanie najkr�tszej �cie�ki w grafie algorytmem Dijkstry
void GraphMatrix::shortestPathDijkstra() {
	int* p = new int[numberOfVertices];
	for (int i = 0; i < numberOfVertices; i++) {
		p[i] = -1;
	}

	int* d = new int [numberOfVertices];
	bool* isVertexChecked = new bool[numberOfVertices];
	for (int i = 0; i < numberOfVertices; i++) {
		d[i] = INT_MAX;
		isVertexChecked[i] = false;
	}
	
	d[startingVertex] = 0;
	
	for (int i = 0; i < numberOfVertices; i++) {
		int indexOfVertex = minimumDistance(d, isVertexChecked);
		isVertexChecked[indexOfVertex] = true;
		for (int j = 0; j < numberOfVertices; j++) {
			if (weightMatrix[indexOfVertex][j] > 0 && d[indexOfVertex] + weightMatrix[indexOfVertex][j] < d[j]) {
				d[j] = d[indexOfVertex] + weightMatrix[indexOfVertex][j];
				p[j] = indexOfVertex;
			}
		}
	}

	//printf("End  Dist  Path\n");
	//for (int i = 0; i < numberOfVertices; i++) {
	//	if (d[i] != INT_MAX) {
	//		printf("%4d|%5d|", i, d[i]);
	//		int neighbor = p[i];
	//		string path = " ";
	//		while (neighbor != 0 && i != startingVertex) {
	//			path = to_string(neighbor) + " " + path;
	//			neighbor = p[neighbor];
	//		}
	//		path = "0 " + path;
	//		cout << path << "\n";
	//	} 
	//	else {
	//		printf("%4d|    N|\n", i);
	//		continue;
	//	}
	//}

	delete[] p;
	delete[] d;
	delete[] isVertexChecked;
}

//Wyznaczanie najkr�tszej �cie�ki w grafie algorytmem Bellmana-Forda
void GraphMatrix::shortestPathBellmanFord() {
	int* p = new int[numberOfVertices];
	for (int i = 0; i < numberOfVertices; i++) {
		p[i] = -1;
	}

	int* d = new int[numberOfVertices];
	for (int i = 0; i < numberOfVertices; i++) {
		d[i] = INT_MAX;
	}

	d[startingVertex] = 0;

	//P�tla relaksuj�ca ka�d� kraw�d� V-1 razy
	for (int i = 0; i < numberOfVertices - 1; i++) {
		bool shouldStop = true;
		//P�tla przechodz�ca po ka�dej kraw�dzi
		for (int j = 0; j < numberOfVertices; j++) {
			for (int k = 0; k < numberOfVertices; k++) {
				if (weightMatrix[j][k] > 0 && d[j] + weightMatrix[j][k] < d[k]) {
					d[k] = d[j] + weightMatrix[j][k];
					p[k] = j;
					shouldStop = false;
				}
			}
			
		}
		if (shouldStop) break;
	}


	//Wykrycie ujemnych cykli
	for (int i = 0; i < numberOfVertices; i++) {
		for (int j = 0; j < numberOfVertices; j++) {
			if (weightMatrix[i][j] > 0 && d[i] != INT_MAX && d[i] + weightMatrix[i][j] < d[j]) {
				cout << "Wykryto cykl ujemny";
				return;
			}
		}
	}

	/*printf("End  Dist  Path\n");
	for (int i = 0; i < numberOfVertices; i++) {
		if (d[i] != INT_MAX) {
			printf("%4d|%5d|", i, d[i]);
			int neighbor = p[i];
			string path = " ";
			while (neighbor != 0 && i != startingVertex) {
				path = to_string(neighbor) + " " + path;
				neighbor = p[neighbor];
			}
			path = "0 " + path;
			cout << path << "\n";
		}
		else {
			printf("%4d|    N|\n", i);
			continue;
		}
	}*/

	delete[] p;
	delete[] d;
}

int GraphMatrix::minimumDistance(int* d, bool* isVertexChecked) {
	int min = INT_MAX;
	int index = 0;
	for (int i = 0; i < numberOfVertices; i++) {
		if (!isVertexChecked[i] && d[i] < min) {
			min = d[i];
			index = i;
		}
	}
	return index;
}

int** GraphMatrix::getWeightMatrix() {
	return weightMatrix;
}

int GraphMatrix::getNumberOfEdges() {
	return numberOfEdges;
}

int GraphMatrix::getNumberOfVertices() {
	return numberOfVertices;
}

//Odczyt grafu z pliku
void GraphMatrix::readFromFile(string fileName) {
	if (weightMatrix != nullptr) dropGraph();
	fstream file;
	file.open(fileName, ios::in);
	if (file.is_open()) {
		int numberOfEdges;
		file >> numberOfEdges;

		int numberOfVertices;
		file >> numberOfVertices;
		allocateArray(numberOfVertices);

		file >> this->startingVertex;
		file >> this->endingVertex;
		
		for (int i = 0; i < numberOfEdges; i++) {
			int startingVertex;
			file >> startingVertex;
			int endingVertex;
			file >> endingVertex;
			int weight;
			file >> weight;
			addEdge(startingVertex, endingVertex, weight);
		}
	}
	else {
		cout << "Blad otwarcia pliku\n";
	}

}

//Wyznaczanie minimalnego drzewa rozpinaj�cego algorytmem Prima
void GraphMatrix::mstPrim() {

	int* p = new int[numberOfVertices];
	for (int i = 0; i < numberOfVertices; i++) {
		p[i] = -2;
	}

	int* key = new int[numberOfVertices];
	bool* isInSet = new bool[numberOfVertices];
	for (int i = 0; i < numberOfVertices; i++) {
		key[i] = INT_MAX;
		isInSet[i] = false;
	}

	key[0] = 0;
	p[0] = -1;

	for (int i = 0; i < numberOfVertices-1; i++) {
		int vertexToSet = minimumDistance(key, isInSet);

		isInSet[vertexToSet] = true;

		for (int j = 0; j < numberOfVertices; j++) {
			if (weightMatrix[vertexToSet][j] > 0 && !isInSet[j] && weightMatrix[vertexToSet][j] < key[j]) {
				p[j] = vertexToSet;
				key[j] = weightMatrix[vertexToSet][j];
			}
		}
	}

	//Wypisanie krawedzi drzewa mst
	/*cout << "Edge         Weight\n";
	for (int i = 0; i < numberOfVertices; i++) {
		if (key[i] != INT_MAX && key[i] != 0) {
			printf("(%2d, %2d)   %2d\n", p[i], i, key[i]);
		}
	}
	
	int sumOfMst = 0;
	for (int i = 0; i < numberOfVertices; i++) {
		sumOfMst += key[i];
	}
	cout << "\nMST = " << sumOfMst << "\n";
	*/
	delete[] p;
	delete[] key;
	delete[] isInSet;
}


//Wyznaczanie minimalnego drzewa rozpinaj�cego algorytmem Kruskala
void GraphMatrix::mstKruskal() {
	int* parents = new int[numberOfVertices];
	for (int i = 0; i < numberOfVertices; i++) {
		parents[i] = i;
	}

	int* ranks = new int[numberOfVertices];
	for (int i = 0; i < numberOfVertices; i++) {
		ranks[i] = 0;
	}

	int sumOfMst = 0;
	int counterOfMstEdges = 0;
	while (counterOfMstEdges < numberOfVertices - 1) {
		int min = INT_MAX;
		int a = -1;
		int b = -1;
		for (int i = 0; i < numberOfVertices; i++) {
			for (int j = 0; j < numberOfVertices; j++) {
				if (findSet(i, parents) != findSet(j, parents) && weightMatrix[i][j] != INT_MIN && weightMatrix[i][j] < min) {
					min = weightMatrix[i][j];
					a = i;
					b = j;
				}
			}
		}
		
		unionSubgraphs(a, b, parents, ranks);
		printf("(%2d, %2d)   %2d\n", a, b, min);
		counterOfMstEdges++;
		sumOfMst += min;
	}
	
	cout << "\nMST = " << sumOfMst << "\n";

	delete[] parents;
	delete[] ranks;
}

//Wyznaczanie maksymalnego przep�ywu algorytmem Forda Fulkersona
void GraphMatrix::maximumFlowFordFulkerson() {
	int** residualGraph = new int*[numberOfVertices];
	for (int i = 0; i < numberOfVertices; i++) {
		residualGraph[i] = new int[numberOfVertices];
		for (int j = 0; j < numberOfVertices; j++) {
			if (weightMatrix[i][j] != INT_MIN)
				residualGraph[i][j] = weightMatrix[i][j];
			else
				residualGraph[i][j] = 0;
			
		}
	}

	int* parent = new int[numberOfVertices];
	int maxFlow = 0;

	while (dfsMatrix(residualGraph, startingVertex, endingVertex, parent, numberOfVertices)) {
		int pathFlow = INT_MAX;
		for (int i = endingVertex; i != startingVertex; i = parent[i]) {
			int j = parent[i];
			pathFlow = min(pathFlow, residualGraph[j][i]);
		}

		for (int i = endingVertex; i != startingVertex; i = parent[i]) {
			int j = parent[i];
			residualGraph[j][i] -= pathFlow;
			residualGraph[i][j] += pathFlow;
		}

		maxFlow += pathFlow;
	}

	cout << "Edge       Flow (max / used)\n";
	for (int i = 0; i < numberOfVertices; i++) {
		for (int j = 0; j < numberOfVertices; j++) {
			if (weightMatrix[i][j] > 0)
				printf("(%2d, %2d)   %2d / %2d\n", i, j, weightMatrix[i][j], residualGraph[j][i]);
		}
	}
	cout << "MAX_FLOW = " << maxFlow << "\n";
}



