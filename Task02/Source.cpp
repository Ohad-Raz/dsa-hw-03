#include <iostream>
#include <vector>
#include <queue>
#include <windows.h> 
#include <climits>

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
    for (int r = 0; r < ROWS; r++)
        for (int c = 0; c < COLS; c++) {
            grid[r][c] = '.';
            dist[r][c] = INT_MAX;
            visited[r][c] = false;
            prev_cell[r][c] = { -1, -1 };
        }

    
    for (int r = 5; r <= 15; r++)
        grid[r][20] = '#';
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
                cout << "a";           
            else
                cout << grid[r][c];    
        }
        cout << endl;
    }
    Sleep(10); 
}


void dijkstra(int startRow, int startCol, int endRow, int endCol) {
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

        print_grid(current.row, current.col, startRow, startCol, endRow, endCol);
    }

  
    int r = endRow, c = endCol;
    while (prev_cell[r][c].first != -1) {
        auto [pr, pc] = prev_cell[r][c];
        if (!(r == startRow && c == startCol) && grid[r][c] != 'B') {
            grid[r][c] = '*';
        }
        r = pr;
        c = pc;
        print_grid(-1, -1, startRow, startCol, endRow, endCol);
    }
}

pair<int, int> get_position(const string& label) {
    int row, col;
    while (true) {
        cout << "Enter " << label << " position (row 1-20, col 1-40): ";
        cin >> row >> col;
        if (row >= 1 && row <= ROWS && col >= 1 && col <= COLS)
            break;
        cout << "Invalid position. Please enter values within grid range.\n";
    }
    return { row - 1, col - 1 };  
}

int main() {

    initialize_grid();
    print_grid();

    auto [startRow, startCol] = get_position("START");
    auto [endRow, endCol] = get_position("END");

    grid[endRow][endCol] = 'B';

    dijkstra(startRow, startCol, endRow, endCol);
    print_grid(-1, -1, startRow, startCol, endRow, endCol);
    cout << "\n Pathfinding complete.\n";

    return 0;
}
