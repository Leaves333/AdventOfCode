#include <bits\stdc++.h>
using namespace std;

const bool fileIO = true;
void setIO() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
}

int main() {

    if (fileIO) { setIO(); }

    bool board[1000][1000];
    memset(board, false, sizeof(board));
    
    static int bright[1000][1000];
    memset(bright, 0, sizeof(bright));

    for (int i = 0; i < 300; i++) {

        //parse command
        string str; cin >> str;
        if (str[1] == 'u') cin >> str;
        string command = str;

        string coords; cin >> coords;
        int a = stoi(coords.substr(0, coords.find(","))), b = stoi(coords.substr(coords.find(",") + 1));

        cin >> coords; //get rid of "through"
        cin >> coords;
        int x = stoi(coords.substr(0, coords.find(","))), y = stoi(coords.substr(coords.find(",") + 1));

        for (int i = a; i <= x; i++) {
            for (int j = b; j <= y; j++) {
                if (command == "toggle") {
                    board[i][j] = !board[i][j];
                    bright[i][j] += 2;
                }
                else if (command == "on") {
                    board[i][j] = true;
                    bright[i][j]++;
                }
                else if (command == "off") {
                    board[i][j] = false;
                    bright[i][j] = max(0, bright[i][j] - 1);
                }
            }
        }

    }

    int ans = 0;
    int anss = 0;
    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 1000; j++) {
            if (board[i][j]) { ans++; }
            anss += bright[i][j];
        }
    }
    cout << ans << endl << anss;

}