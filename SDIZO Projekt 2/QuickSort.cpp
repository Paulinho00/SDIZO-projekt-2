#include "Graphs.h"

int partitionOfArray(Edge* edgesArray, int low, int high) {
	int pivot = edgesArray[high].weight;
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++) {
		if (edgesArray[j].weight < pivot) {
			i++;
			Edge temporary = edgesArray[i];
			edgesArray[i] = edgesArray[j];
			edgesArray[j] = temporary;
		}
	}

	Edge temporary = edgesArray[i + 1];
	edgesArray[i + 1] = edgesArray[high];
	edgesArray[high] = temporary;
	return (i + 1);
}

void sortEdgesArray(Edge* edgesArray, int low, int high) {
	if (low < high) {
		int pi = partitionOfArray(edgesArray, low, high);

		sortEdgesArray(edgesArray, low, pi - 1);
		sortEdgesArray(edgesArray, pi + 1, high);
	}
}