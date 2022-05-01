#include <string>


//Graf w reprezentacji macierzowej
class GraphMatrix{
	//Macierz wag krawêdzi
	int** weightMatrix;
	//Liczba wierzcho³ków
	int numberOfVertices;
	//Liczba krawêdzi
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
	//Wyœwietlenie grafu w odpowiedniej reprezentacji
	void showGraph();
	//Wyznaczanie minimalnego drzewa rozpinaj¹cego algorytmem Kruskala
	void mstKruskal();
	//Wyznaczanie minimalnego drzewa rozpinaj¹cego algorytmem Prima
	void mstPrim();
	//Wyznaczanie najkrótszej œcie¿ki w grafie algorytmem Dijkstry
	void shortestPathDijkstra();
	//Wyznaczanie najkrótszej œcie¿ki w grafie algorytmem Bellmana-Forda
	void shortestPathBellmanFord();
	//Wyznaczanie maksymalnego przep³ywu algorytmem Forda Fulkersona
	void maximumFlowFordFulkerson();

	int** getWeightMatrix();
	int getNumberOfEdges();
	int getNumberOfVertices();
private:
	//Zwraca indeks wierzcholka z najmniejszym dystansem
	int minimumDistance(int* d, bool* isVertexChecked);
	//Usuwa graf
	void dropGraph();
	//Dodaje krawêdŸ grafu
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
	//Wskazniki na listy s¹siadów wierzcho³ków
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
	//Wyœwietlenie grafu
	void showGraph();
	//Wyznaczanie minimalnego drzewa rozpinaj¹cego algorytmem Kruskala
	void mstKruskal();
	//Wyznaczanie minimalnego drzewa rozpinaj¹cego algorytmem Prima
	void mstPrim();
	//Wyznaczanie najkrótszej œcie¿ki w grafie algorytmem Dijkstry
	void shortestPathDijkstra();
	//Wyznaczanie najkrótszej œcie¿ki w grafie algorytmem Bellmana-Forda
	void shortestPathBellmanFord();
	//Wyznaczanie maksymalnego przep³ywu algorytmem Forda Fulkersona
	void maximumFlowFordFulkerson();

private:
	void dropGraph();
	void addEdge(int firstVertex, int secondVertex, int weight);
	//Zwraca indeks wierzcholka z najmniejszym dystansem
	int minimumDistance(int* d, bool* isVertexChecked);
};