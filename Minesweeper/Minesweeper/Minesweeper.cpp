// Minesweeper.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <ctime> // std::time
#include <random> // std::mt19937
#include <array>
#include <algorithm>

constexpr int ROWS{ 7 };
constexpr int COLUMNS{ 7 };
constexpr int MINES{ 12 };
int MATRIX[ROWS][COLUMNS]{};
char B_MATRIX[ROWS][COLUMNS]{};
char UI_MATRIX[ROWS][COLUMNS]{};


void printMatrix(char MATRIX[][COLUMNS]) {

	std::cout << "    ";
	for (int i = 0; i < COLUMNS; i++){
		std::cout << i + 1 << ' ';
	}
	std::cout << '\n';
	std::cout << "   ";
	
	for (int i = 0; i < COLUMNS; i++){
		std::cout << "--";
	}
	std::cout << '\n';

	for (int i = 0; i < ROWS; i++) {
		std::cout << i + 1 << " | ";
		for (int j = 0; j < COLUMNS; j++) {
			std::cout << MATRIX[i][j] << ' ';
		}
		std::cout << '\n';
	} 
}

void generateMines() {
	
	static std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };

	int k{ 0 };
	do {
		int row{ mt() % ROWS };  // alege un rand si o coloana random
		int column{ mt() % COLUMNS };

		if (B_MATRIX[row][column] != '*') {
			B_MATRIX[row][column] = '*';
			k++;
		}
		// plasam mine pana ajungem la nr total
	} while (k != MINES);  
	

	for (int i = 0; i < ROWS; i++) { // generare matrice cu indici
		for (int j = 0; j < COLUMNS; j++) {
	
			UI_MATRIX[i][j] = '?';  // genram matrice ui(doar playeru poate sa o vada)
		}
		//std::cout << '\n';
	}
	// amplasare mine fara dubluri
	// trb sortat bombs nu ia ultima linie INCEP DE LA 0 U DUMBFUCK
}

bool isValid(int row, int column) {

	if (row >= 0 && row < ROWS && column >= 0 && column < COLUMNS) // verificam daca indicele de rand sau coloana e in afaara matricei
		return true;
	else
		return false;
}
int numberOfNeighbours(int row, int column) {

	int neighbours{ 0 };  // pt fiecare celula verificam toti vecinii daca sunt mine
	// linia de sus
	if (isValid(row - 1, column - 1) && B_MATRIX[row - 1][column - 1] == '*')
		neighbours++;
	if (isValid(row - 1, column) && B_MATRIX[row - 1][column] == '*')
		neighbours++;
	if (isValid(row - 1, column + 1) && B_MATRIX[row - 1][column + 1] == '*')
		neighbours++;  

	// linia de mijloc
	if (isValid(row , column - 1) && B_MATRIX[row][column - 1] == '*')
		neighbours++;
	if (isValid(row , column + 1) && B_MATRIX[row][column + 1] == '*')
		neighbours++;

	// linia de jos
	if (isValid(row + 1, column - 1) && B_MATRIX[row + 1][column - 1] == '*')
		neighbours++;
	if (isValid(row + 1, column) && B_MATRIX[row + 1][column] == '*')
		neighbours++;
	if (isValid(row + 1, column + 1) && B_MATRIX[row + 1][column + 1] == '*')
		neighbours++;

	return neighbours;
}

void generateNumbers() {

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			if (B_MATRIX[i][j] != '*')
				B_MATRIX[i][j] = static_cast<char>(numberOfNeighbours(i, j) + 48); // conversie din int in char +48(pt ca ascii)
		}
	}
}

bool isBomb(int row, int column) {
	return(B_MATRIX[row][column] == '*'); //verificam dace e mina
}

void replaceCell(int row, int column) {

	UI_MATRIX[row][column] = B_MATRIX[row][column]; // inlocuim celula din matricea ui
}

void placeBomb(int row, int column) {
	UI_MATRIX[row][column] = '*';  // playeru plaseaza bomba
}

void playGame() {
	std::cout << "WELCOME TO MINESWEEPER!\n";
	int row{};
	int column{};
	int choice{};

	while (true) {

		printMatrix(UI_MATRIX);
		std::cout << "Choose an option: \n";
		std::cout << "1. Reveal a cell(row,column): \n";
		std::cout << "2. Mark a cell(row,column) as a bomb: \n";

		std::cin >> choice;
		std::cout << "row:  ";
		std::cin >> row;
		std::cout << "column:  ";
		std::cin >> column;
		std::cout << '\n';

		if (isBomb(row - 1, column - 1)) {  // -1 pt ca incepem de la 0 dar playerul alege de la 1
			std::cout << "GAME OVER!\n";
			printMatrix(B_MATRIX);
			return;
		}
		else {
			if (choice == 1) {
				replaceCell(row - 1, column - 1);
			}
			else {
				placeBomb(row - 1, column - 1);
			}
			
			//printMatrix(UI_MATRIX);
		}
	}
}
int main()
{
	generateMines();
	generateNumbers();
	//printMatrix(B_MATRIX);
	playGame();
}

