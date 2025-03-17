#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

int field[100][100];
int field_p[100][100];
int N = 0, M = 0, K = 0;

void print_field() {
	system("cls");
	cout << "  ";
	for (int i = 0; i < M; ++i) {
		cout << " " << i + 1;
		if (i + 1 < 10) cout << " ";
	}
	cout << endl;
	for (int i = 0; i < N; i++) {
		cout << i + 1 << " ";
		if (i + 1 < 10) {
			cout << " ";
		}
		for (int j = 0; j < M; j++) {
			if (field_p[i][j] == -2) {
				cout << "_  ";
			}
			else if (field_p[i][j] == -1) {
				cout << "f  ";
			}
			else if (field_p[i][j] == -3) {
				cout << "*  ";
			}
			else {
				cout << field_p[i][j] << "  ";
			}
		}
		cout << endl;
	}
	cout << endl << endl;
}

void dfs(int x, int y) {
	if (x < 0 || x >= N || y < 0 || y >= M || field_p[x][y] > -2) return;
	field_p[x][y] = field[x][y];
	if (field[x][y] > 0) return;
	for (int i2 = x - 1; i2 <= x + 1; ++i2) {
		for (int j2 = y - 1; j2 <= y + 1; ++j2) {
			if (i2 != x || j2 != y) dfs(i2, j2);
		}
	}
}

bool open_cell(int x, int y) {
	if (field[x][y] == -1) {
		return false;
	}
	else if (field[x][y] > 0) {
		field_p[x][y] = field[x][y];
		return true;
	}
	else if (field[x][y] == 0) {
		dfs(x, y);
		return true;
	}
}

bool is_win() {
	int opened = 0;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; j++) {
			if (field_p[i][j] >= 0) opened++;
		}
	}
	return (N * M - K == opened);
}

void end_game(bool  is_win = false) {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; j++) {
			if (field_p[i][j] == -1) field_p[i][j] = -2;
			if (field[i][j] == -1) field_p[i][j] = -3;
		}
	}
	print_field();
	cout << "Вы " << (is_win ? "выиграли" : "проиграли") << "!\nЧтобы начать новую игру введите любую строку:\n";
	string s;
	cin >> s;
}

int zapusk() {
	int z = 0;
	while (true) {
		cout << "Вы выберите режим: \n";
		cout << "1 - Новичок: 9х9\n";
		cout << "2 - Любитель : 16х16\n";
		cout << "3 - Профессионал: 16х30\n";
		cout << "4 - Выход\n";
		cout << "Выбираю режим: ";
		cin >> z;
		if (z == 1) {
			N = 9, M = 9, K = 10;
			break;
		}
		else if (z == 2) {
			N = 16, M = 16, K = 40;
			break;
		}
		else if (z == 3) {
			N = 16, M = 30, K = 99;
			break;
		}
		else if (z == 4) {
			return 4;
		}
		else {
			cout << "Такого режима нет!\n";
		}
	}
}

int main() {
	setlocale(LC_ALL, "Russian");
	if (zapusk() == 4) {
		return 0;
	}
	//от времени
	srand(time(0));
	while (true) {
		//обнуляем поле
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				field[i][j] = 0;
				field_p[i][j] = -2;
			}
		}
		for (int i = 0; i < K; ++i) {
			while (true) {
				int x = rand() % N;
				int y = rand() % M;
				if (field[x][y] != -1) {
					field[x][y] = -1;
					break;
				}
			}
		}
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; j++) {
				if (field[i][j] != -1) {
					field[i][j] = 0;
					for (int i2 = i - 1; i2 <= i + 1; ++i2) {
						for (int j2 = j - 1; j2 <= j + 1; ++j2) {
							if (i2 >= 0 && i2 < N && j2 >= 0 && j2 < M && field[i2][j2] == -1) {
								++field[i][j];
							}
						}
					}
				}
			}
		}

		while (true) {
			print_field();
			cout << "Список команд: \n";
			cout << "\\o x y - открыть клетку\n";
			cout << "\\f x y - поставить флажок\n";
			cout << "\\n - новая игра\n";
			cout << "\\q - выход\n";
			cout << "Введите команду: ";
			/*
			\o x y
			\f x y
			\n
			\q
			*/
			string command;
			cin >> command;
			if (command == "\\o") {
				//ввод координат
				int x, y;
				cin >> x >> y;
				--x; --y;
				if (x < 0 || x >= N || y < 0 || y >= M || field_p[x][y] >= 0) continue;
				//откроем клетки
				if (!open_cell(x, y)) {
					end_game();
					break;
				}
				if (is_win()) {
					end_game(true);
					break;
				}
			}
			else if (command == "\\f") {
				//ввод координат
				int x, y;
				cin >> x >> y;
				--x; --y;
				if (x < 0 || x >= N || y < 0 || y >= M || field_p[x][y] >= 0) continue;
				//ставим флаг
				if (field_p[x][y] == -1) {
					field_p[x][y] = -2;
				}
				else {
					field_p[x][y] = -1;
				}
			}
			else if (command == "\\n") {
				//новая игра
				break;
			}
			else if (command == "\\q") {
				//выход
				return 0;
			}
		}
	}
}