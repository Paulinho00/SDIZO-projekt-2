#include "Graphs.h"
#include <iostream>
#include <string>
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
		}; break;
		case 2: {
			cout << "Podaj ilosc wierzcholkow: ";
			userInput = readUserInput();
			if (userInput <= 0) {
				cout << "Nieprawdilowe dane\n";
				break;
			}
			cout << "Podaj gestosc grafu (od 0% do %100): ";
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
			cout << "Podaj gestosc grafu (od 0% do %100): ";
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
			cout << "Reprezentacja macierzowa: \n";
			graphMatrix.shortestPathDijkstra();
			cout << "\nReprezentacja listowa: \n";
			graphList.shortestPathDijkstra();
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
		case 0: return;
		default: cout << "Nie ma takiej opcji\n";
		};

	}
}



int main()
{
	mainMenu();
}
