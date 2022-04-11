#include <string>


//Klasa abstrakcyjna z funkcjami grafu dla obu reprezentacji
class Graph {
public:
	//Losowe generowanie grafu
	virtual void generateGraph(int vertices, int density);
	//Odczyt grafu z pliku
	virtual void readFromFile(std::string fileName);
	//Wy�wietlenie grafu w odpowiedniej reprezentacji
	virtual void showGraph();
	//Wyznaczanie minimalnego drzewa rozpinaj�cego algorytmem Kruskala
	virtual void mstKruskal();
	//Wyznaczanie minimalnego drzewa rozpinaj�cego algorytmem Prima
	virtual void mstPrim();
	//Wyznaczanie najkr�tszej �cie�ki w grafie algorytmem Dijkstry
	virtual void shortestPathDijkstra();
	//Wyznaczanie najkr�tszej �cie�ki w grafie algorytmem Bellmana-Forda
	virtual void shortestPathBellmanFord();
	//Wyznaczanie maksymalnego przep�ywu algorytmem Forda Fulkersona
	virtual void maximumFlowFordFulkerson();
};


//Graf w reprezentacji macierzowej
class GraphMatrix : public Graph {
	//Macierz wag kraw�dzi
	int** weightMatrix;
public:
	GraphMatrix();
	~GraphMatrix();
};

//Graf w reprezentacji listowej
class GraphList : public Graph {
	//Wskazniki na listy s�siad�w wierzcho�k�w
	int* pointersToList;
public:
	GraphList();
	~GraphList();
};