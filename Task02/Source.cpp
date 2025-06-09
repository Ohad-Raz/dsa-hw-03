#include <iostream>
#include <vector>
#include <queue>
#include <windows.h>
#include <climits>
#include <algorithm>
using namespace std;

const int ROWS = 20;
const int COLS = 40;

struct Cell {
	int row, col;
	int dist;
	bool operator>(const Cell& other) const {
		return dist > other.dist;
	}
};

char grid[ROWS][COLS];
int dist[ROWS][COLS];
bool visited[ROWS][COLS];
pair<int, int> prev_cell[ROWS][COLS];

int dRow[] = { -1, 1, 0, 0 };
int dCol[] = { 0, 0, -1, 1 };

bool is_valid(int row, int col) {
	return row >= 0 && row < ROWS && col >= 0 && col < COLS && grid[row][col] != '#' && !visited[row][col];
}

void initialize_grid() {
	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLS; c++) {
			grid[r][c] = '.';
			dist[r][c] = INT_MAX;
			visited[r][c] = false;
			prev_cell[r][c] = { -1, -1 };
		}
	}

	for (int r = 5; r <= 15; r++)
		grid[r][20] = '#';

	for (int r = 5; r <= 10; r++)
		grid[r][10] = '#';
}

void print_grid(int currentRow = -1, int currentCol = -1, int startRow = -1, int startCol = -1, int endRow = -1, int endCol = -1) {
	system("cls");
	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLS; c++) {
			if (r == startRow && c == startCol)
				cout << "A"; 
			else if (r == endRow && c == endCol)
				cout << "B"; 
			else if (r == currentRow && c == currentCol)
				cout << "X"; 
			else if (grid[r][c] == '#')
				cout << "#"; 
			else
				cout << ".";
		}
		cout << endl;
	}
	Sleep(100);
}

vector<pair<int, int>> dijkstra(int startRow, int startCol, int endRow, int endCol) {
	priority_queue<Cell, vector<Cell>, greater<Cell>> pq;
	dist[startRow][startCol] = 0;
	pq.push({ startRow, startCol, 0 });

	while (!pq.empty()) {
		Cell current = pq.top(); pq.pop();

		if (visited[current.row][current.col]) continue;
		visited[current.row][current.col] = true;

		if (current.row == endRow && current.col == endCol)
			break;

		for (int i = 0; i < 4; i++) {
			int newRow = current.row + dRow[i];
			int newCol = current.col + dCol[i];

			if (is_valid(newRow, newCol)) {
				int newDist = dist[current.row][current.col] + 1;
				if (newDist < dist[newRow][newCol]) {
					dist[newRow][newCol] = newDist;
					prev_cell[newRow][newCol] = { current.row, current.col };
					pq.push({ newRow, newCol, newDist });
				}
			}
		}
	}

	vector<pair<int, int>> path;
	int r = endRow, c = endCol;
	while (prev_cell[r][c].first != -1) {
		path.push_back({ r, c });
		tie(r, c) = prev_cell[r][c];
	}
	path.push_back({ startRow, startCol });
	reverse(path.begin(), path.end());

	return path;
}


pair<int, int> get_position(const string& label) {
	int row, col;
	while (true) {
		cout << "Enter " << label << " position (row 1-20, col 1-40): ";
		cin >> row >> col;

		row--; col--;  // converting to 0 based

		if (row >= 0 && row < ROWS && col >= 0 && col < COLS) {
			if (grid[row][col] != '#') {
				return { row, col };
			}
			else {
				cout << "That position is a wall. Choose a different location."<<endl;
			}
		}
		else {
			cout << "Invalid position. Please enter values within grid range."<<endl;
		}
	}
}

int main() {
	initialize_grid();

	auto [startRow, startCol] = get_position("START");
	auto [endRow, endCol] = get_position("END");

	vector<pair<int, int>> path = dijkstra(startRow, startCol, endRow, endCol);

	for (auto [r, c] : path) {
		print_grid(r, c, startRow, startCol, endRow, endCol);
	}

	cout << "\nA reached destination B!"<<endl;
	return 0;
}
