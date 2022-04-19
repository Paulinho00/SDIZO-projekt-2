#include "Graphs.h"
#include <iostream>
using namespace std;

ListElement::ListElement(int key, int weight) {
	this->key = key;
	this->weight = weight;
	currentFlow = 0;
	nextElement = nullptr;
}

ListElement::~ListElement() {
	delete nextElement;
}

GraphList::GraphList(bool isDirected) {
	numberOfEdges = 0;
	numberOfVertices = 0;
	pointersToList = nullptr;
	this->isDirected = isDirected;
}

GraphList::~GraphList() {
	dropGraph();
}

//Losowe generowanie grafu
void GraphList::generateGraph(int** weightMatrix, int numberOfVertices) {
	if (pointersToList != nullptr) dropGraph();
	this->numberOfVertices = numberOfVertices;
	pointersToList = new ListElement* [numberOfVertices];
	for (int i = 0; i < numberOfVertices; i++) {
		pointersToList[i] = nullptr;
	}

	for (int i = 0; i < numberOfVertices; i++) {
		ListElement* list = pointersToList[i];
		for (int j = i; j < numberOfVertices; j++) {
			if (weightMatrix[i][j] != INT_MIN) {
				addEdge(i, j, weightMatrix[i][j]);
			}
		}
	}
}

//Wyœwietlenie grafu
void GraphList::showGraph() {
	if (isDirected) { showDirectedGraph(); }
	else { showUndirectedGraph(); }
}

//Wyœwietlenie grafu w odpowiedniej reprezentacji
void GraphList::showDirectedGraph() {
	cout << "\n";
	for (int i = 0; i < numberOfVertices; i++) {
		cout << i << ": ";
		ListElement* list = pointersToList[i];
		if (list != nullptr) {
			cout << "(" << list->key;
			if (list->weight < 0) {
				cout << ", k)";
			}
			else {
				cout << ", p)";
			}
			list = list->nextElement;
			while (list != nullptr) {
				cout << "-> (" << list->key;
				if (list->weight < 0) {
					cout << ", k)";
				}
				else {
					cout << ", p)";
				}
				list = list->nextElement;
			}
		}
		cout << "\n";
	}
}

//Wyœwietlenie grafu w odpowiedniej reprezentacji
void GraphList::showUndirectedGraph() {
	cout << "\n";
	for (int i = 0; i < numberOfVertices; i++) {
		cout << i << ": ";
		ListElement* list = pointersToList[i];
		if (list != nullptr) {
			cout << list->key;
			list = list->nextElement;
			while (list != nullptr) {
				cout << "-> " << list->key;
				list = list->nextElement;
			}
		}
		cout << "\n";
	}
}

void GraphList::addEdge(int firstVertex, int secondVertex, int weight) {
	if (pointersToList[firstVertex] == nullptr) {
		pointersToList[firstVertex] = new ListElement(secondVertex, weight);
	}
	else {
		ListElement* firstVertexElement = pointersToList[firstVertex];
		while (firstVertexElement->nextElement != nullptr) {
			firstVertexElement = firstVertexElement->nextElement;
		}
		firstVertexElement->nextElement = new ListElement(secondVertex, weight);
	}

	if (isDirected) { weight *= -1; }

	if (pointersToList[secondVertex] == nullptr) {
		pointersToList[secondVertex] = new ListElement(firstVertex, weight);
	}
	else {
		ListElement* secondVertexElement = pointersToList[secondVertex];
		while (secondVertexElement->nextElement != nullptr) {
			secondVertexElement = secondVertexElement->nextElement;
		}
		secondVertexElement->nextElement = new ListElement(firstVertex, weight);
	}
	
	numberOfEdges++;
}

void GraphList::dropGraph() {
	for (int i = 0; i < numberOfVertices; i++) {
		delete pointersToList[i];
	}
	delete pointersToList;
}
