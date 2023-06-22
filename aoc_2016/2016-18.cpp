#include <bits\stdc++.h>
using namespace std;

const bool fileIO = true;
void setIO() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
}

int main() {

    if (fileIO) { setIO(); }

    string cur = ".^.^..^......^^^^^...^^^...^...^....^^.^...^.^^^^....^...^^.^^^...^^^^.^^.^.^^..^.^^^..^^^^^^.^^^..^";
    int emptySpaces = 0;

    for (int i = 0; i < 400000; i++) {

        for (auto c : cur) {
            if (c == '.') {
                emptySpaces++;
            }
        }

        string next = "";
        for (int j = 0; j < cur.length(); j++) {

            bool left = true, center = cur[j] == '^', right = true;
            if (j - 1 < 0 || cur[j - 1] == '.') {
                left = false;
            }
            if (j + 1 >= cur.length() || cur[j + 1] == '.') {
                right = false;
            }

            if (left && !center && !right) {
                next += "^";
            }
            else if (!left && !center && right) {
                next += "^";
            }
            else if (left && center && !right) {
                next += "^";
            }
            else if (!left && center && right) {
                next += "^";
            }
            else {
                next += ".";
            }

        }
        cur = next;

    }

    cout << emptySpaces;

}