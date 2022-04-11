#include <string>


//Klasa abstrakcyjna z funkcjami grafu dla obu reprezentacji
class Graph {
public:
	//Losowe generowanie grafu
	virtual void generateGraph(int vertices, int density);
	//Odczyt grafu z pliku
	virtual void readFromFile(std::string fileName);
	//Wyœwietlenie grafu w odpowiedniej reprezentacji
	virtual void showGraph();
	//Wyznaczanie minimalnego drzewa rozpinaj¹cego algorytmem Kruskala
	virtual void mstKruskal();
	//Wyznaczanie minimalnego drzewa rozpinaj¹cego algorytmem Prima
	virtual void mstPrim();
	//Wyznaczanie najkrótszej œcie¿ki w grafie algorytmem Dijkstry
	virtual void shortestPathDijkstra();
	//Wyznaczanie najkrótszej œcie¿ki w grafie algorytmem Bellmana-Forda
	virtual void shortestPathBellmanFord();
	//Wyznaczanie maksymalnego przep³ywu algorytmem Forda Fulkersona
	virtual void maximumFlowFordFulkerson();
};


//Graf w reprezentacji macierzowej
class GraphMatrix : public Graph {
	//Macierz wag krawêdzi
	int** weightMatrix;
public:
	GraphMatrix();
	~GraphMatrix();
};

//Graf w reprezentacji listowej
class GraphList : public Graph {
	//Wskazniki na listy s¹siadów wierzcho³ków
	int* pointersToList;
public:
	GraphList();
	~GraphList();
};