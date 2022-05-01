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
void GraphMatrix::shortestPathDijkstra(int startVertex) {
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
	
	d[startVertex] = 0;
	
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
			while (neighbor != 0 && i != startVertex) {
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
