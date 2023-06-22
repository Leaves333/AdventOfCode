#include <bits\stdc++.h>
using namespace std;

const bool fileIO = true;
void setIO() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
}

int clamp (int low, int high, int x) {
    if (x < low) {
        return low;
    }
    if (x > high) {
        return high;
    }
    return x;
}

int main() {

    if (fileIO) { setIO(); }
    bool part1 = false;
    string ans = "";

    int x = 1, y = 1;
    if (!part1) {
        x = 0, y = 2; 
    }

    string keypad[5][5] = { { "X", "X", "1", "X", "X" },
                            { "X", "2", "3", "4", "X" },
                            { "5", "6", "7", "8", "9" },
                            { "X", "A", "B", "C", "X" },
                            { "X", "X", "D", "X", "X" } };

    for (int k = 0; k < 5; k++) {

        string instructions;
        cin >> instructions;

        if (part1) {
            for (int i = 0; i < instructions.length(); i++) {

                if (instructions[i] == 'U') {
                    y--;
                }
                else if (instructions[i] == 'D') {
                    y++;
                }
                else if (instructions[i] == 'L') {
                    x--;
                }
                else if (instructions[i] == 'R') {
                    x++;
                }

                if (x < 0) {
                    x = 0;
                }
                if (x > 2) {
                    x = 2;
                }
                if (y < 0) {
                    y = 0;
                }
                if (y > 2) {
                    y = 2;
                }

            }
            int number = (y * 3) + x + 1;
            ans += to_string(number);
        }
        else {

            for (int i = 0; i < instructions.length(); i++) {

                if (instructions[i] == 'U') {
                    int newY = clamp(0, 4, y - 1);
                    if (keypad[newY][x] != "X") {
                        y = newY;
                    }
                }
                else if (instructions[i] == 'D') {
                    int newY = clamp(0, 4, y + 1);
                    if (keypad[newY][x] != "X") {
                        y = newY;
                    }
                }
                else if (instructions[i] == 'L') {
                    int newX = clamp(0, 4, x - 1);
                    if (keypad[y][newX] != "X") {
                        x = newX;
                    }
                }
                else if (instructions[i] == 'R') {
                    int newX = clamp(0, 4, x + 1);
                    if (keypad[y][newX] != "X") {
                        x = newX;
                    }
                }

            }

            ans += keypad[y][x];

        }

    }

    cout << ans;

}