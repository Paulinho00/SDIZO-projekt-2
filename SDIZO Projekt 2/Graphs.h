#include <string>


//Graf w reprezentacji macierzowej
class GraphMatrix{
	//Macierz wag kraw�dzi
	int** weightMatrix;
	//Liczba wierzcho�k�w
	int numberOfVertices;
	//Liczba kraw�dzi
	int numberOfEdges;
public:
	GraphMatrix(int numberOfVertices);
	GraphMatrix();
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
private:
	//Usuwa graf
	void dropGraph();
	//Dodaje kraw�d� grafu
	void addEdge(int firstVertex, int secondVertex, int weight);
	//Alokuje macierz wag w pamieci
	void allocateArray(int numberOfVertices);
};

//Graf w reprezentacji listowej
class GraphList{
	//Wskazniki na listy s�siad�w wierzcho�k�w
	int* pointersToList;
public:
	GraphList(int numberOfVertices);
	~GraphList();

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
};