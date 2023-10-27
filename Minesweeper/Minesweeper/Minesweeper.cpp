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
char B_MATRIX[ROWS][COLUMNS]{}; //  this matrix will only display when the player loses
char UI_MATRIX[ROWS][COLUMNS]{}; // this matrix represents the interface that the player interacts with


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
	// we  generate bombs until we reach the total number of bombs 
	int k{ 0 };
	do {
		int row{ mt() % ROWS };  
		int column{ mt() % COLUMNS };

		if (B_MATRIX[row][column] != '*') {
			B_MATRIX[row][column] = '*';
			k++;
		}
		// if the tile already has a bomb present we will generate another bomb
	} while (k != MINES);  
	

	for (int i = 0; i < ROWS; i++) { 
		for (int j = 0; j < COLUMNS; j++) {
	
			UI_MATRIX[i][j] = '?';  // all the tiles start with the '?' symbol on them
		}
		//std::cout << '\n';
	}
}

bool isValid(int row, int column) {

	if (row >= 0 && row < ROWS && column >= 0 && column < COLUMNS) // we check if the cell is in between bounds
		return true;
	else
		return false;
}
int numberOfNeighbours(int row, int column) {

	int neighbours{ 0 };  // for every neighbouring cells we check if there are bombs
	// the upper cells
	if (isValid(row - 1, column - 1) && B_MATRIX[row - 1][column - 1] == '*')
		neighbours++;
	if (isValid(row - 1, column) && B_MATRIX[row - 1][column] == '*')
		neighbours++;
	if (isValid(row - 1, column + 1) && B_MATRIX[row - 1][column + 1] == '*')
		neighbours++;  

	// the middle line
	if (isValid(row , column - 1) && B_MATRIX[row][column - 1] == '*')
		neighbours++;
	if (isValid(row , column + 1) && B_MATRIX[row][column + 1] == '*')
		neighbours++;

	// the lower cells
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
				B_MATRIX[i][j] = static_cast<char>(numberOfNeighbours(i, j) + 48); // we insert the number representing the number of bombs nearby 
		}
	}
}

bool isBomb(int row, int column) {
	return(B_MATRIX[row][column] == '*'); 
}

void replaceCell(int row, int column) {

	UI_MATRIX[row][column] = B_MATRIX[row][column]; 
}

void placeBomb(int row, int column) {
	UI_MATRIX[row][column] = '*';  // the player places a bomb in the UI matrix
}

bool isWon() {
	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLUMNS; j++)
			if (B_MATRIX[i][j] != UI_MATRIX[i][j])
				return false;
	return true;
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

		}

		if (isWon())
			std::cout << "\nYOU WIN!\n";
	}
}
int main()
{
	generateMines();
	generateNumbers();

	playGame();
}

