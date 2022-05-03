#include <string>


//Graf w reprezentacji macierzowej
class GraphMatrix{
	//Macierz wag kraw�dzi
	int** weightMatrix;
	//Liczba wierzcho�k�w
	int numberOfVertices;
	//Liczba kraw�dzi
	int numberOfEdges;
	//Czy jest skierowany
	bool isDirected;
public:
	int startingVertex;
	int endingVertex;
public:
	GraphMatrix(bool isDirected);
	~GraphMatrix();
	//Losowe generowanie grafu
	void generateGraph(int vertices, float density);
	//Odczyt grafu z pliku
	void readFromFile(std::string fileName);
	//Wy�wietlenie grafu w odpowiedniej reprezentacji
	void showGraph();
	//Wyznaczanie minimalnego drzewa rozpinaj�cego algorytmem Kruskala
	void mstKruskal();
	//Wyznaczanie minimalnego drzewa rozpinaj�cego algorytmem Prima
	void mstPrim();
	//Wyznaczanie najkr�tszej �cie�ki w grafie algorytmem Dijkstry
	void shortestPathDijkstra();
	//Wyznaczanie najkr�tszej �cie�ki w grafie algorytmem Bellmana-Forda
	void shortestPathBellmanFord();
	//Wyznaczanie maksymalnego przep�ywu algorytmem Forda Fulkersona
	void maximumFlowFordFulkerson();

	int** getWeightMatrix();
	int getNumberOfEdges();
	int getNumberOfVertices();
private:
	//Zwraca indeks wierzcholka z najmniejszym dystansem
	int minimumDistance(int* d, bool* isVertexChecked);
	//Usuwa graf
	void dropGraph();
	//Dodaje kraw�d� grafu
	void addEdge(int firstVertex, int secondVertex, int weight);
	//Alokuje macierz wag w pamieci
	void allocateArray(int numberOfVertices);
};

struct ListElement {
	int key;
	int weight;
	int currentFlow;
	ListElement* nextElement;

	ListElement(int key, int weight);
	~ListElement();
};

//Graf w reprezentacji listowej
class GraphList{
	//Wskazniki na listy s�siad�w wierzcho�k�w
	ListElement** pointersToList;
	int numberOfVertices;
	int numberOfEdges;
	//Czy jest skierowany
	bool isDirected;
public:
	int startingVertex;
	int endingVertex;
public:
	GraphList(bool isDirected);
	~GraphList();

	//Losowe generowanie grafu
	void generateGraph(int** weightMatrix, int numberOfVertices);
	//Wy�wietlenie grafu
	void showGraph();
	//Wyznaczanie minimalnego drzewa rozpinaj�cego algorytmem Kruskala
	void mstKruskal();
	//Wyznaczanie minimalnego drzewa rozpinaj�cego algorytmem Prima
	void mstPrim();
	//Wyznaczanie najkr�tszej �cie�ki w grafie algorytmem Dijkstry
	void shortestPathDijkstra();
	//Wyznaczanie najkr�tszej �cie�ki w grafie algorytmem Bellmana-Forda
	void shortestPathBellmanFord();
	//Wyznaczanie maksymalnego przep�ywu algorytmem Forda Fulkersona
	void maximumFlowFordFulkerson();
private:
	void dropGraph();
	void addEdge(int firstVertex, int secondVertex, int weight);
	//Zwraca indeks wierzcholka z najmniejszym dystansem
	int minimumDistance(int* d, bool* isVertexChecked);
};

//Krawedz grafu
struct Edge {
	int startVertex;
	int endVertex;
	int weight;
};

int partitionOfArray(Edge* edgesArray, int low, int high);

void sortEdgesArray(Edge* edgesArray, int low, int high);

//Wyszukiwanie podgrafu dla algorytmu Kruskala
int findSet(int vertex, int* parentsArray);

//��czenie podgraf�w dla algorytmu Kruskala
void unionSubgraphs(int firstVertex, int secondVertex, int* parentsArray, int* ranks);

//Przeszukiwanie w g��b
bool dfs(int** residualGraph, int source, int sink, int parent[], int numberOfVertices);

void dfsVisit(int** residualGraph, int source, int* parent, bool* visited, int numberOfVertices);