#include "Graphs.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <stdio.h>
using namespace std;

GraphMatrix::GraphMatrix(int numberOfVertices) {

}

GraphMatrix::GraphMatrix(){
	weightMatrix = nullptr;
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
	cout << "\n   |";
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
		free(weightMatrix[i]);
	}
	free(weightMatrix);
	weightMatrix = nullptr;
	numberOfEdges = 0;
	numberOfVertices = 0;
}

//Dodaje krawêdŸ grafu
void GraphMatrix::addEdge(int firstVertex, int secondVertex, int weight) {
		weightMatrix[firstVertex][secondVertex] = weight;
		weightMatrix[secondVertex][firstVertex] = weight;
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

