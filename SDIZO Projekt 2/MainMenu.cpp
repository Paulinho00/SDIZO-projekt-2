#include "Graphs.h"
#include <iostream>
#include <string>
#include <windows.h>
#include <iomanip>

using namespace std;

int readUserInput() {
	//Odczyt wyboru uzytkownika
	int userInput;
	cin >> userInput;

	//Wykrycie blednego typu wejscia
	if (cin.fail()) {
		cout << "Podales zla liczbe\n";
		//Wyczyszczenie buforu
		cin.clear();
		cin.ignore(100, '\n');
		return -1;
	}
	else {
		return userInput;
	}
}

//Menu dla problemu mst
void mstMenu() {
	GraphMatrix graphMatrix(false);
	GraphList graphList(false);
	while (1) {
		//Wyswietlenie opcji w menu
		cout << "\nWybierz strukture:\n";
		cout << "1. Wczytywanie danych z pliku\n";
		cout << "2. Generowanie losowego grafu\n";
		cout << "3. Wyswietlanie grafu macierzowo i listowo\n";
		cout << "4. Algorytm Kruskala\n";
		cout << "5. Algorytm Prima\n";
		cout << "0. Cofnij\n";
		cout << "Podaj odpowiednia liczbe: \n";


		//Odczyt wyboru uzytkownika
		int userInput;
		userInput = readUserInput();
		if (userInput == -1) {
			continue;
		}

		//Uruchomienie odpowiedniej funkcji w zaleznosci od wyboru
		switch (userInput) {
		case 1: {
			cout << "Podaj nazwe pliku: ";
			string fileName;
			cin >> fileName;
			graphMatrix.readFromFile(fileName);
			graphList.generateGraph(graphMatrix.getWeightMatrix(), graphMatrix.getNumberOfVertices());
		}; break;
		case 2: {
			cout << "Podaj ilosc wierzcholkow: ";
			userInput = readUserInput();
			if (userInput <= 0) {
				cout << "Nieprawdilowe dane\n";
				break;
			}
			cout << "Podaj gestosc grafu (od 0% do 100%): ";
			int percent = readUserInput();
			float density = percent / 100.0;
			if (density < 0 && density > 1.0) {
				cout << "Nieprawidlowe dane\n";
				break;
			}
			graphMatrix.generateGraph(userInput, density);
			graphList.generateGraph(graphMatrix.getWeightMatrix(), graphMatrix.getNumberOfVertices());
		}; break;
		case 3: {
			cout << "Reprezentacja macierzowa:\n";
			graphMatrix.showGraph();

			cout << "\nReprezentacja listowa:\n";
			graphList.showGraph();
		} break;
		case 4: {
			cout << "\nAlgorytm Kruskala\n";
			cout << "Reprezentacja macierzowa: \n";
			graphMatrix.mstKruskal();
			cout << "\nReprezentacja listowa: \n";
			graphList.mstKruskal();
		}; break;
		case 5: {
			cout << "\nAlgorytm Prima\n";
			cout << "Reprezentacja macierzowa: \n";
			graphMatrix.mstPrim();
			cout << "\nReprezentacja listowa: \n";
			graphList.mstPrim();

		}; break;
		case 0: return;
		default: cout << "Nie ma takiej opcji\n";
		};

	}
}

//Menu dla problemu mst
void shortestPathMenu() {
	GraphMatrix graphMatrix(true);
	GraphList graphList(true);
	while (1) {
		//Wyswietlenie opcji w menu
		cout << "\nWybierz strukture:\n";
		cout << "1. Wczytywanie danych z pliku\n";
		cout << "2. Generowanie losowego grafu\n";
		cout << "3. Wyswietlanie grafu macierzowo i listowo\n";
		cout << "4. Algorytm Dijkstry\n";
		cout << "5. Algorytm Bellmana-Forda\n";
		cout << "0. Cofnij\n";
		cout << "Podaj odpowiednia liczbe: \n";


		//Odczyt wyboru uzytkownika
		int userInput;
		userInput = readUserInput();
		if (userInput == -1) {
			continue;
		}

		//Uruchomienie odpowiedniej funkcji w zaleznosci od wyboru
		switch (userInput) {
		case 1: {
			cout << "Podaj nazwe pliku: ";
			string fileName;
			cin >> fileName;
			graphMatrix.readFromFile(fileName);
			graphList.generateGraph(graphMatrix.getWeightMatrix(), graphMatrix.getNumberOfVertices());
		}; break;
		case 2: {
			cout << "Podaj ilosc wierzcholkow: ";
			userInput = readUserInput();
			if (userInput <= 0) {
				cout << "Nieprawdilowe dane\n";
				break;
			}
			cout << "Podaj gestosc grafu (od 0% do 100%): ";
			int percent = readUserInput();
			float density = percent / 100.0;
			if (density < 0 && density > 1.0) {
				cout << "Nieprawidlowe dane\n";
				break;
			}
			graphMatrix.generateGraph(userInput, density);
			graphList.generateGraph(graphMatrix.getWeightMatrix(), graphMatrix.getNumberOfVertices());
		}; break;
		case 3: {
			cout << "Reprezentacja macierzowa:\n";
			graphMatrix.showGraph();

			cout << "\nReprezentacja listowa:\n";
			graphList.showGraph();
		} break;
		case 4: {
			cout << "Aktualnie wybrany wierzcholek: " << graphMatrix.startingVertex << "\n";
			cout << "Podaj wierzcholek startowy:\n";
			userInput = readUserInput();
			if (userInput < 0) {
				cout << "Nieprawdilowe dane\n";
				break;
			}

			graphMatrix.startingVertex = userInput;
			graphList.startingVertex = userInput;
			
			cout << "\nAlgorytm Dijkstry\n";
			cout << "Reprezentacja macierzowa: \n";
			graphMatrix.shortestPathDijkstra();
			cout << "\nReprezentacja listowa: \n";
			graphList.shortestPathDijkstra();
		}; break;
		case 5: {
			cout << "Aktualnie wybrany wierzcholek: " << graphMatrix.startingVertex << "\n";
			cout << "Podaj wierzcholek startowy:\n";
			userInput = readUserInput();
			if (userInput < 0) {
				cout << "Nieprawdilowe dane\n";
				break;
			}

			graphMatrix.startingVertex = userInput;
			graphList.startingVertex = userInput;

			cout << "\nAlgorytm Bellmana-Forda\n";
			cout << "Reprezentacja macierzowa: \n";
			graphMatrix.shortestPathBellmanFord();
			cout << "\nReprezentacja listowa: \n";
			graphList.shortestPathBellmanFord();
		}; break;
		case 0: return;
		default: cout << "Nie ma takiej opcji\n";
		};

	}
}

//Menu dla problemu mst
void flowMenu() {
	GraphMatrix graphMatrix(true);
	GraphList graphList(true);
	while (1) {
		//Wyswietlenie opcji w menu
		cout << "\nWybierz strukture:\n";
		cout << "1. Wczytywanie danych z pliku\n";
		cout << "2. Generowanie losowego grafu\n";
		cout << "3. Wyswietlanie grafu macierzowo i listowo\n";
		cout << "4. Algorytm Forda-Fulkersona\n";
		cout << "0. Cofnij\n";
		cout << "Podaj odpowiednia liczbe: \n";


		//Odczyt wyboru uzytkownika
		int userInput;
		userInput = readUserInput();
		if (userInput == -1) {
			continue;
		}

		//Uruchomienie odpowiedniej funkcji w zaleznosci od wyboru
		switch (userInput) {
		case 1: {
			cout << "Podaj nazwe pliku: ";
			string fileName;
			cin >> fileName;
			graphMatrix.readFromFile(fileName);
			graphList.generateGraph(graphMatrix.getWeightMatrix(), graphMatrix.getNumberOfVertices());
		}; break;
		case 2: {
			cout << "Podaj ilosc wierzcholkow: ";
			userInput = readUserInput();
			if (userInput <= 0) {
				cout << "Nieprawdilowe dane\n";
				break;
			}
			cout << "Podaj gestosc grafu (od 0% do 100%): ";
			int percent = readUserInput();
			float density = percent / 100.0;
			if (density < 0 && density > 1.0) {
				cout << "Nieprawidlowe dane\n";
				break;
			}
			graphMatrix.generateGraph(userInput, density);
			graphList.generateGraph(graphMatrix.getWeightMatrix(), graphMatrix.getNumberOfVertices());
		}; break;
		case 3: {
			cout << "Reprezentacja macierzowa:\n";
			graphMatrix.showGraph();

			cout << "\nReprezentacja listowa:\n";
			graphList.showGraph();
		} break;
		case 4: {
			cout << "Aktualnie wybrany wierzcholek: " << graphMatrix.startingVertex << "\n";
			cout << "Podaj wierzcholek startowy:\n";
			userInput = readUserInput();
			if (userInput < 0) {
				cout << "Nieprawdilowe dane\n";
				break;
			}

			graphMatrix.startingVertex = userInput;
			graphList.startingVertex = userInput;

			cout << "Aktualnie wybrany wierzcholek: " << graphMatrix.endingVertex << "\n";
			cout << "Podaj wierzcholek koncowy:\n";
			userInput = readUserInput();
			if (userInput < 0) {
				cout << "Nieprawdilowe dane\n";
				break;
			}

			graphMatrix.endingVertex = userInput;
			graphList.endingVertex = userInput;

			cout << "\nAlgorytm Forda-Fulkersona\n";
			cout << "Reprezentacja macierzowa: \n";
			graphMatrix.maximumFlowFordFulkerson();
			cout << "\nReprezentacja listowa: \n";
			graphList.maximumFlowFordFulkerson();
			graphList.resetFlows();
		}; break;
		case 0: return;
		default: cout << "Nie ma takiej opcji\n";
		};

	}
}

void mainMenu() {
	while (1) {
		//Wyswietlenie opcji w menu
		cout << "\nWybierz strukture:\n";
		cout << "1. Wyznaczanie minimalnego drzewa rozpinajacego (MST)\n";
		cout << "2. Wyznaczanie najkrotszej sciezki w grafie\n";
		cout << "3. Wyznaczanie maksymalnego przeplywu\n";
		cout << "0. Zakoncz program\n";
		cout << "Podaj odpowiednia liczbe: \n";


		//Odczyt wyboru uzytkownika
		int userInput;
		userInput = readUserInput();
		if (userInput == -1) {
			continue;
		}

		//Uruchomienie odpowiedniej funkcji w zaleznosci od wyboru
		switch (userInput) {
		case 1: mstMenu(); break;
		case 2: shortestPathMenu(); break;
		case 3: flowMenu(); break;
		case 0: return;
		default: cout << "Nie ma takiej opcji\n";
		};

	}
}

long long int read_QPC()
{
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return((long long int)count.QuadPart);
}


int main()
{

	long long int frequency, start, elapsed;
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
	float density = 0.99;
	double sum = 0;
	double unit = 1000.0;

	for (int i = 0; i < 100; i++) {
		GraphMatrix graphMatrix(false);
		graphMatrix.generateGraph(50, density);
		start = read_QPC();
		graphMatrix.mstKruskal();
		elapsed = read_QPC() - start;
		sum += (unit * elapsed)/ frequency;
	}
	sum /= 100;
	cout << "Dla 50: " << sum << "us" << endl << endl;

	for (int i = 0; i < 100; i++) {
		GraphMatrix graphMatrix(false);
		graphMatrix.generateGraph(100, density);
		start = read_QPC();
		graphMatrix.mstKruskal();
		elapsed = read_QPC() - start;
		sum += (unit * elapsed) / frequency;
	}
	sum /= 100;
	cout << "Dla 100: " << sum << "us" << endl << endl;

	for (int i = 0; i < 100; i++) {
		GraphMatrix graphMatrix(false);
		graphMatrix.generateGraph(150, density);
		start = read_QPC();
		graphMatrix.mstKruskal();
		elapsed = read_QPC() - start;
		sum += (unit * elapsed) / frequency;
	}
	sum /= 100;
	cout << "Dla 150: " << sum << "us" << endl << endl;

	for (int i = 0; i < 100; i++) {
		GraphMatrix graphMatrix(false);
		graphMatrix.generateGraph(200, density);
		start = read_QPC();
		graphMatrix.mstKruskal();
		elapsed = read_QPC() - start;
		sum += (unit * elapsed) / frequency;
	}
	sum /= 100;
	cout << "Dla 200: " << sum << "us" << endl << endl;

	for (int i = 0; i < 100; i++) {
		GraphMatrix graphMatrix(false);
		graphMatrix.generateGraph(250, density);
		start = read_QPC();
		graphMatrix.mstKruskal();
		elapsed = read_QPC() - start;
		sum += (unit * elapsed) / frequency;
	}
	sum /= 100;
	cout << "Dla 250: " << sum << "us" << endl << endl;

	for (int i = 0; i < 100; i++) {
		GraphMatrix graphMatrix(false);
		graphMatrix.generateGraph(300, density);
		start = read_QPC();
		graphMatrix.mstKruskal();
		elapsed = read_QPC() - start;
		sum += (unit * elapsed) / frequency;
	}
	sum /= 100;
	cout << "Dla 300: " << sum << "us" << endl << endl;

	for (int i = 0; i < 100; i++) {
		GraphMatrix graphMatrix(false);
		graphMatrix.generateGraph(350, density);
		start = read_QPC();
		graphMatrix.mstKruskal();
		elapsed = read_QPC() - start;
		sum += (unit * elapsed) / frequency;
	}
	sum /= 100;
	cout << "Dla 350: " << sum << "us" << endl << endl;

	for (int i = 0; i < 100; i++) {
		GraphMatrix graphMatrix(false);
		graphMatrix.generateGraph(400, density);
		start = read_QPC();
		graphMatrix.mstKruskal();
		elapsed = read_QPC() - start;
		sum += (unit * elapsed) / frequency;
	}
	sum /= 100;
	cout << "Dla 400: " << sum << "us" << endl << endl;
}
