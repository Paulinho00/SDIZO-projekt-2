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