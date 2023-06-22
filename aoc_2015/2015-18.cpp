#include <bits\stdc++.h>
using namespace std;

const bool fileIO = true;
void setIO() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
}

const int INPUT_SIZE = 100;
bool validIndex(int x, int y) {
    return (x >= 0 && x < INPUT_SIZE) && (y >= 0 && y < INPUT_SIZE);
}

int main() {

    if (fileIO) { setIO(); }
    
    bool board[INPUT_SIZE][INPUT_SIZE];

    for (int i = 0; i < INPUT_SIZE; i++) {
        for (int j = 0; j < INPUT_SIZE; j++) {
            char c; cin >> c;
            if (c == '#') {
                board[i][j] = true;
            }
            else {
                board[i][j] = false;
            }
        } 
    }

    for (int k = 0; k < 100; k++) {

        bool newBoard[INPUT_SIZE][INPUT_SIZE];
        memcpy(newBoard, board, sizeof(board));

        for (int x = 0; x < INPUT_SIZE; x++) {
            for (int y = 0; y < INPUT_SIZE; y++) {

                int neighbors = 0;
                for (int i = -1; i <= 1; i++) {
                    for (int j = -1; j <= 1; j++) {
                        if (validIndex(x + i, y + j) && board[x + i][y + j]) {
                            neighbors++;
                        }
                    }
                }
                if (board[x][y]) { neighbors--; } //don't factor in current cell

                if (board[x][y]) {
                    if (neighbors < 2 || neighbors > 3) {
                        newBoard[x][y] = false;
                    }
                }
                else {
                    if (neighbors == 3) {
                        newBoard[x][y] = true;
                    }
                }

            }
        }

        //part 2
        if (true) {
            newBoard[0][0] = true;
            newBoard[0][INPUT_SIZE - 1] = true;
            newBoard[INPUT_SIZE - 1][0] = true;
            newBoard[INPUT_SIZE - 1][INPUT_SIZE - 1] = true;
        }
        
        memcpy(board, newBoard, sizeof(newBoard));        

    }

    int ans = 0;
    for (int i = 0; i < INPUT_SIZE; i++) {
        for (int j = 0; j < INPUT_SIZE; j++) {
            if (board[i][j]) {
                ans++;
            }
        }
    }

    cout << ans;

}