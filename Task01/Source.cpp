#include <iostream>
#include <windows.h>  
using namespace std;

const int ROWS = 20;
const int COLS = 40;

void print_grid(int currentRow, int currentCol, int endRow, int endCol) {
    system("cls");

    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            if (row == currentRow && col == currentCol) {
                cout << "A"; 
            }
            else if (row == endRow && col == endCol) {
                cout << "B"; 
            }
            else {
                cout << ".";
            }
        }
        cout << endl;
    }
}

int main() {
    int startRow, startCol, endRow, endCol;

    cout << "Enter START position (row and column, 1-based): ";
    cin >> startRow >> startCol;
    cout << "Enter END position (row and column, 1-based): ";
    cin >> endRow >> endCol;

    
    startRow--; startCol--;
    endRow--; endCol--;

    int currentRow = startRow;
    int currentCol = startCol;

    while (currentRow != endRow || currentCol != endCol) {
        print_grid(currentRow, currentCol, endRow, endCol);
        Sleep(100);

        if (currentRow < endRow) currentRow++;
        else if (currentRow > endRow) currentRow--;

        if (currentCol < endCol) currentCol++;
        else if (currentCol > endCol) currentCol--;
    }

    
    print_grid(currentRow, currentCol, endRow, endCol);
    cout << "\nReached destination!\n";

    return 0;
}
