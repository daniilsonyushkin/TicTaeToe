#include <iostream>

using namespace std;  

const int SIZE = 3;  // размер игрового поля 3 на 3
const int CELL_HEIGHT = 3;  // высота одной клетки в символах
const int CELL_WIDTH = 5;   // ширина одной клетки в символах

// функция для отображения игрового поля с красивыми символами
void displayBoard(const char board[SIZE][SIZE]) {
	cout << "\n";  // Начинаем с новой строки

	// идем по строкам в обратном порядке ( от 2 до 0 )
	for (int i = SIZE - 1; i >= 0; i--) {
		for (int line = 0; line < CELL_HEIGHT; line++) {
			for (int j = 0; j < SIZE; j++) {  
				cout << "|";  

				
				if (board[i][j] == 'X') {
					switch (line) {
					case 0: cout << " \\ / "; break;  
					case 1: cout << "  X  "; break;  
					case 2: cout << " / \\ "; break;  
					}
				}
				else if (board[i][j] == 'O') {
					switch (line) {
					case 0: cout << " *** "; break;  
					case 1: cout << " * * "; break;  
					case 2: cout << " *** "; break;  
					}
				}
				else {
					switch (line) {
					case 0: cout << "     "; break;  
					case 1: cout << "  " << i * 3 + j + 1 << "  "; break;  
					case 2: cout << "     "; break;  
					}
				}
			}
			cout << "|\n";  
		}

		// горизонтальная линия между строками ( кроме последней итерации )
		if (i > 0) {
			for (int j = 0; j < SIZE; j++) {
				cout << "+";  // Угол клетки
				for (int k = 0; k < CELL_WIDTH; k++) cout << "-";  
			}
			cout << "+\n";  
		}
	}
	cout << "\n";  
}

// Проверка победы игрока
bool checkWin(const char board[SIZE][SIZE], char player) {
	for (int i = 0; i < SIZE; ++i) {
		if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||  
			(board[0][i] == player && board[1][i] == player && board[2][i] == player)) {  
			return true;
		}
	}

	// Проверяем диагонали
	if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||  
		(board[0][2] == player && board[1][1] == player && board[2][0] == player)) {  
		return true;
	}

	return false;  
}

// Проверка на ничью
bool checkDraw(const char board[SIZE][SIZE]) {
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			if (board[i][j] == ' ') {  
				return false;  
			}
		}
	}
	return true;  // если все клетки заполнены - ничья
}

// получение хода от игрока
void getPlayerMove(char board[SIZE][SIZE], char player) {
	int cell;
	while (true) {  
		cout << "Игрок " << player << ", введите номер клетки (1-9): ";
		cin >> cell;

		if (cin.fail()) {  
			cin.clear();  
			cin.ignore('\n');  
			cout << "Некорректный ввод. Пожалуйста, введите число.\n";
			continue;
		}

		if (cell < 1 || cell > 9) {  // если число вне диапазона
			cout << "Некорректный ввод. Число должно быть от 1 до 9.\n";
			continue;
		}

		int row = (cell - 1) / 3;  
		int col = (cell - 1) % 3;  

		if (board[row][col] != ' ') {  
			cout << "Эта клетка уже занята. Выберите другую.\n";
			continue;
		}

		board[row][col] = player;  
		break;  
	}
}

int main() {
	char board[SIZE][SIZE] = { {' ', ' ', ' '},  
							  {' ', ' ', ' '},
							  {' ', ' ', ' '} };
	char currentPlayer = 'X';  
	bool gameOver = false;     // Флаг окончания игры
	setlocale(LC_ALL, "RUS");  
	cout << "Добро пожаловать в игру Крестики-нолики!\n";
	cout << "Игрок X ходит первым, затем игрок O.\n";
	cout << "Для хода введите номер клетки (1-9), как показано на поле.\n";

	while (!gameOver) {  
		displayBoard(board);  
		getPlayerMove(board, currentPlayer);  

		if (checkWin(board, currentPlayer)) {  
			displayBoard(board);
			cout << "Игрок " << currentPlayer << " победил! Поздравляем!\n";
			gameOver = true;
		}
		else if (checkDraw(board)) {  
			displayBoard(board);
			cout << "Ничья! Игра окончена.\n";
			gameOver = true;
		}
		else {
			currentPlayer = (currentPlayer == 'X') ? 'O' : 'X'; 
		}
	}

	cout << "Спасибо за игру!\n";  

	return 0;
}