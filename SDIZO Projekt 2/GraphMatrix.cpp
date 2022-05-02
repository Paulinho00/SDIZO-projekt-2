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

	//Sprawdzenie czy mo¿na utworzyæ graf rozpinaj¹cy przy danej gêstoœci
	if (desiredNumberOfEdges < (vertices - 1)) {
		cout << "Gestosc jest za niska dla tej liczby wierzcholkow (nie mozna utworzyc grafu rozpinajacego)\n";
		return;
	}
	
	//Generowanie drzewa rozpinaj¹cego
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

	//Generowanie dodatkowych krawêdzi, aby osiagnac odpowiednia gestosc
	while (numberOfEdges < desiredNumberOfEdges) {
		int firstVertexToEdge = rand() % numberOfVertices;
		int secondVertexToEdge = rand() % numberOfVertices;
		randomWeight = rand() % 20 + 1;
		if (firstVertexToEdge != secondVertexToEdge && weightMatrix[firstVertexToEdge][secondVertexToEdge] == INT_MIN) {
			addEdge(firstVertexToEdge, secondVertexToEdge, randomWeight);
		}
	}

}

//Wyœwietlenie grafu w odpowiedniej reprezentacji
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

//Dodaje krawêdŸ grafu
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

		//Wypelnienie macierzy wartoœciami -inf oznaczaj¹cymi brak po³¹czenia
		for (int j = 0; j < numberOfVertices; j++) {
			weightMatrix[i][j] = INT_MIN;
		}
	}
}

//Wyznaczanie najkrótszej œcie¿ki w grafie algorytmem Dijkstry
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

	printf("End  Dist  Path\n");
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
	}

	delete[] p;
	delete[] d;
	delete[] isVertexChecked;
}

//Wyznaczanie najkrótszej œcie¿ki w grafie algorytmem Bellmana-Forda
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

	//Pêtla relaksuj¹ca ka¿d¹ krawêdŸ V-1 razy
	for (int i = 0; i < numberOfVertices - 1; i++) {
		bool shouldStop = true;
		//Pêtla przechodz¹ca po ka¿dej krawêdzi
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

	printf("End  Dist  Path\n");
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
	}

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

//Wyznaczanie minimalnego drzewa rozpinaj¹cego algorytmem Prima
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
	cout << "Edge         Weight\n";
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

	delete[] p;
	delete[] key;
	delete[] isInSet;
}


//Wyznaczanie minimalnego drzewa rozpinaj¹cego algorytmem Kruskala
void GraphMatrix::mstKruskal() {
	int* parents = new int[numberOfVertices];
	for (int i = 0; i < numberOfVertices; i++) {
		parents[i] = i;
	}

	int* ranks = new int[numberOfVertices];
	for (int i = 0; i < numberOfVertices; i++) {
		ranks[i] = 0;
	}

	Edge* edges = new Edge[numberOfEdges];
	int counterOfEdges = 0;
	//Tworzenie listy krawedzi
	for (int i = 0; i < numberOfVertices; i++) {
		for (int j = i+1; j < numberOfVertices; j++) {
			if (weightMatrix[i][j] > 0) {
				edges[counterOfEdges].startVertex = i;
				edges[counterOfEdges].endVertex = j;
				edges[counterOfEdges].weight = weightMatrix[i][j];
				counterOfEdges++;
			}
		}
	}
	sortEdgesArray(edges, 0, numberOfEdges-1);

	Edge* mstEdges = new Edge[numberOfVertices - 1];
	int counterOfMstEdges = 0;

	for (int i = 0; i < numberOfEdges; i++) {
		Edge edgeToBeChecked = edges[i];
		if (findSet(edgeToBeChecked.startVertex, parents) != findSet(edgeToBeChecked.endVertex, parents)) {
			mstEdges[counterOfMstEdges] = edgeToBeChecked;
			unionSubgraphs(edgeToBeChecked.startVertex, edgeToBeChecked.endVertex, parents, ranks);
			counterOfMstEdges++;
		}
	}

	//Wypisanie krawedzi drzewa mst
	cout << "Edge         Weight\n";
	for (int i = 0; i < counterOfMstEdges; i++) {
		printf("(%2d, %2d)   %2d\n", mstEdges[i].startVertex, mstEdges[i].endVertex, mstEdges[i].weight);
	}

	int sumOfMst = 0;
	for (int i = 0; i < counterOfMstEdges; i++) {
		sumOfMst += mstEdges[i].weight;
	}
	cout << "\nMST = " << sumOfMst << "\n";

	delete[] parents;
	delete[] ranks;
	delete[] edges;
	delete[] mstEdges;
}



