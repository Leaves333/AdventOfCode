#include <bits\stdc++.h>
using namespace std;

const bool fileIO = true;
void setIO() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
}

bool board[50][50];
int dist[50][50];

void dfs(int x, int y, int moves) {

    if (moves >= dist[x][y]) {
        return;
    }
    dist[x][y] = moves;

    //check final destination
    if (x == 31 && y == 39) {
        //ans = min(moves, ans);
        return;
    }

    if (x > 0 && board[x - 1][y]) {
        dfs(x - 1, y, moves + 1);
    }

    if (x < 50 && board[x + 1][y]) {
        dfs(x + 1, y, moves + 1);
    }

    if (y > 0 && board[x][y - 1]) {
        dfs(x, y - 1, moves + 1);
    }

    if (y < 50 && board[x][y + 1]) {
        dfs(x, y + 1, moves + 1);
    }

}

int main() {

    if (fileIO) { setIO(); }
    int input = 1364;

    //generate board
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 50; j++) {

            int cell = (i * i) + (3 * i) + (2 * i * j) + (j) + (j * j);
            cell += input;
            int bits = 0;
            while (cell > 0) {
                if (cell % 2 == 1) {
                    bits++;
                }
                cell /= 2;
            }

            if (bits % 2 == 0) {
                board[i][j] = true;
            }
            else {
                board[i][j] = false;
            }

        }
    }

    for (auto &a : dist) {
        for (auto &b : a) {
            b = INT_MAX;
        }
    }

    //do dfs
    dfs(1, 1, 0);
    int ans = 0;

    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 50; j++) {
            if (dist[i][j] <= 50) ans++;
        }
    }

    cout << dist[31][39] << endl;
    cout << ans << endl;

}