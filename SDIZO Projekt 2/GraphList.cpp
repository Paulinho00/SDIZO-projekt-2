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


//Generowanie grafu na podstawie grafu w reprezentacji macierzowej
void GraphList::generateGraph(int** weightMatrix, int numberOfVertices) {
	if (pointersToList != nullptr) dropGraph();
	this->numberOfVertices = numberOfVertices;
	pointersToList = new ListElement* [numberOfVertices];
	for (int i = 0; i < numberOfVertices; i++) {
		pointersToList[i] = nullptr;
	}

	for (int i = 0; i < numberOfVertices; i++) {
		ListElement* list = pointersToList[i];
		int j;
		if (isDirected) j = 0;
		else j = i;
		for (; j < numberOfVertices; j++) {
			if (weightMatrix[i][j] != INT_MIN) {
				addEdge(i, j, weightMatrix[i][j]);
			}
		}
	}
}

//Wyœwietlenie grafu
void GraphList::showGraph() {
	cout << "\n";
	for (int i = 0; i < numberOfVertices; i++) {
		cout << i << ": ";
		ListElement* list = pointersToList[i];
		if (list != nullptr) {
			cout << "(" << list->key << ", " << list->weight << ")";
			list = list->nextElement;
			while (list != nullptr) {
				cout << ", (" << list->key << ", " << list->weight << ")";
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

	if (!isDirected) {

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
	}
	
	numberOfEdges++;
}

void GraphList::dropGraph() {
	for (int i = 0; i < numberOfVertices; i++) {
		delete pointersToList[i];
	}
	delete pointersToList;
	numberOfEdges = 0;
	numberOfVertices = 0;
}

//Wyznaczanie najkrótszej œcie¿ki w grafie algorytmem Dijkstry
void GraphList::shortestPathDijkstra() {
	int* p = new int[numberOfVertices];
	for (int i = 0; i < numberOfVertices; i++) {
		p[i] = -1;
	}

	int* d = new int[numberOfVertices];
	bool* isVertexChecked = new bool[numberOfVertices];
	for (int i = 0; i < numberOfVertices; i++) {
		d[i] = INT_MAX;
		isVertexChecked[i] = false;
	}

	d[startingVertex] = 0;

	for (int i = 0; i < numberOfVertices; i++) {
		int indexOfVertex = minimumDistance(d, isVertexChecked);
		isVertexChecked[indexOfVertex] = true;
		ListElement* edge = pointersToList[indexOfVertex];
		while (edge) {
			if (edge->weight > 0 && d[indexOfVertex] + edge->weight < d[edge->key]) {
				d[edge->key] = d[indexOfVertex] + edge->weight;
				p[edge->key] = indexOfVertex;
			}
			edge = edge->nextElement;
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
void GraphList::shortestPathBellmanFord() {
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
			ListElement* edge = pointersToList[j];
			while (edge) {
				if (edge->weight > 0 && d[j] + edge->weight < d[edge->key]) {
					d[edge->key] = d[j] + edge->weight;
					p[edge->key] = j;
					shouldStop = false;
				}
				edge = edge->nextElement;
			}
		}
		if (shouldStop) break;
	}

	//Wykrycie ujemnych cykli
	for (int i = 0; i < numberOfVertices; i++) {
		ListElement* edge = pointersToList[i];
		while(edge) {
			if (edge->weight > 0 && d[i] != INT_MAX && d[i] + edge->weight < d[edge->key]) {
				cout << "Wykryto cykl ujemny";
				return;
			}
			edge = edge->nextElement;
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

//Zwraca indeks wierzcholka z najmniejszym dystansem
int GraphList::minimumDistance(int* d, bool* isVertexChecked) {
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

//Wyznaczanie minimalnego drzewa rozpinaj¹cego algorytmem Prima
void GraphList::mstPrim() {
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

	for (int i = 0; i < numberOfVertices; i++) {
		int vertexToSet = minimumDistance(key, isInSet);

		isInSet[vertexToSet] = true;

		ListElement* neighbor = pointersToList[vertexToSet];
		while (neighbor) {
			if (!isInSet[neighbor->key] && neighbor->weight < key[neighbor->key]) {
				p[neighbor->key] = vertexToSet;
				key[neighbor->key] = neighbor->weight;
			}
			neighbor = neighbor->nextElement;
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
void GraphList::mstKruskal() {
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
		ListElement* neighbor = pointersToList[i];
		while (neighbor) {
			if (neighbor->key > i) {
				edges[counterOfEdges].startVertex = i;
				edges[counterOfEdges].endVertex = neighbor->key;
				edges[counterOfEdges].weight = neighbor->weight;
				counterOfEdges++;
			}
			neighbor = neighbor->nextElement;
		}
	}
	sortEdgesArray(edges, 0, numberOfEdges - 1);

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