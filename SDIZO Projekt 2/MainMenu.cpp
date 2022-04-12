#include "Graphs.h"
#include <iostream>
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
	GraphMatrix g;
	while (1) {
		//Wyswietlenie opcji w menu
		cout << "\nWybierz strukture:\n";
		cout << "1. Wczytywanie danych z pliku\n";
		cout << "2. Generowanie losowego grafu\n";
		cout << "3. Wyœwietlanie grafu macierzowo i listowo\n";
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
			g.generateGraph(userInput, density);
		}; break;
		case 3: g.showGraph(); break;
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
		case 0: return;
		default: cout << "Nie ma takiej opcji\n";
		};

	}
}



int main()
{
	mainMenu();
}
