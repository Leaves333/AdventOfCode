#include <bits\stdc++.h>
using namespace std;

const bool fileIO = true;
void setIO() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
}

int main() {

    if (fileIO) { setIO(); }
    bool board[50][6];
    memset(board, false, sizeof(board));

    for (int k = 0; k < 153; k++) {
        
        string str;
        getline(cin, str);

        vector<string> input;
        while (str.find(" ") != string::npos) {
            input.push_back(str.substr(0, str.find(" ")));
            str.erase(0, str.find(" ") + 1);
        }
        input.push_back(str);

        if (input[0] == "rect") {
            int x = stoi(input[1].substr(0, input[1].find("x")));
            int y = stoi(input[1].substr(input[1].find("x") + 1));
            for (int i = 0; i < x; i++) {
                for (int j = 0; j < y; j++) {
                    board[i][j] = true;
                }
            }
        }
        else if (input[0] == "rotate") {
            int index = stoi(input[2].substr(input[2].find("=") + 1));
            int amount = stoi(input[4]);
            bool rotateRow = input[1] == "row";

            if (rotateRow) {
                for (int i = 0; i < amount; i++) {
                    for (int j = 49; j > 0; j--) {
                        bool tmp = board[j - 1][index];
                        board[j - 1][index] = board[j][index];
                        board[j][index] = tmp;
                    }
                }
            }
            else {
                for (int i = 0; i < amount; i++) {
                    for (int j = 5; j > 0; j--) {
                        bool tmp = board[index][j - 1];
                        board[index][j - 1] = board[index][j];
                        board[index][j] = tmp;
                    }
                }
            }
        }

        for (int j = 0; j < 6; j++) {
            for (int i = 0; i < 50; i++) {
                if (board[i][j]) cout << "#";
                else cout << ".";   
            }
            cout << endl;
        }
        cout << endl;
    }

    int ans = 0;
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 6; j++) {
            if (board[i][j]) {
                ans++;
            }
        }
    }
    cout << ans;

}