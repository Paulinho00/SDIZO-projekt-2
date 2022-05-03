#include "Graphs.h"

//Wyszukiwanie podgrafu dla algorytmu Kruskala
int findSet(int vertex, int* parentsArray) {

	if (parentsArray[vertex] != vertex) {
		parentsArray[vertex] = findSet(parentsArray[vertex], parentsArray);
	}
	return parentsArray[vertex];
}

//£¹czenie podgrafów dla algorytmu Kruskala
void unionSubgraphs(int firstVertex, int secondVertex, int* parentsArray, int* ranks) {
	int parentOfFirstVertex = findSet(firstVertex, parentsArray);
	int parentOfSecondVertex = findSet(secondVertex, parentsArray);

	if (ranks[parentOfFirstVertex] < ranks[parentOfSecondVertex]) {
		parentsArray[parentOfFirstVertex] = parentOfSecondVertex;
	}
	else {
		parentsArray[parentOfSecondVertex] = parentOfFirstVertex;
	}

	if (ranks[parentOfFirstVertex] == ranks[parentOfSecondVertex]) {
		ranks[parentOfFirstVertex] = ranks[parentOfFirstVertex] + 1;
	}
}

bool dfsMatrix(int** residualGraph, int source, int sink, int* parent, int numberOfVertices) {
	bool* visited = new bool[numberOfVertices];
	for (int i = 0; i < numberOfVertices; i++) {
		visited[i] = false;
	}

	visited[source] = true;
	parent[source] = -1;
	for (int i = 0; i < numberOfVertices; i++) {
		if (!visited[i] && residualGraph[source][i] > 0) {
			parent[i] = source;
			visited[i] = true;
			dfsVisitMatrix(residualGraph, i, parent, visited, numberOfVertices);
			if (visited[sink]) return true;
		}

	}

	return (visited[sink] == true);
}

void dfsVisitMatrix(int** residualGraph, int source, int* parent, bool* visited, int numberOfVertices) {
	
	for (int i = 0; i < numberOfVertices; i++) {
		if (!visited[i] && residualGraph[source][i] > 0) {
			parent[i] = source;
			visited[i] = true;
			dfsVisitMatrix(residualGraph, i, parent, visited, numberOfVertices);
		}
	}
}

bool dfsList(ListElement** pointerToList, int source, int sink, int* parent, int numberOfVertices) {
	bool* visited = new bool[numberOfVertices];
	for (int i = 0; i < numberOfVertices; i++) {
		visited[i] = false;
	}

	visited[source] = true;
	parent[source] = -1;
	ListElement* adjacencyList = pointerToList[source];
		while (adjacencyList) {
			if (!visited[adjacencyList->key] && adjacencyList->capacity > 0) {
				parent[adjacencyList->key] = source;
				visited[adjacencyList->key] = true;
				dfsVisitList(pointerToList, adjacencyList->key, parent, visited, numberOfVertices);
				if (visited[sink]) return true;
			}
			adjacencyList = adjacencyList->nextElement;
		}
	return (visited[sink] == true);
}

void dfsVisitList(ListElement** pointerToList, int source, int* parent, bool* visited, int numberOfVertices) {
	ListElement* adjacencyList = pointerToList[source];
	while (adjacencyList) {
		if (!visited[adjacencyList->key] && adjacencyList->capacity> 0) {
			parent[adjacencyList->key] = source;
			visited[adjacencyList->key] = true;
			dfsVisitList(pointerToList, adjacencyList->key, parent, visited, numberOfVertices);
		}
		adjacencyList = adjacencyList->nextElement;
	}
}

