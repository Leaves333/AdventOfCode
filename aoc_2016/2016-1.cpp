#include <bits\stdc++.h>
using namespace std;

const bool fileIO = true;
void setIO() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
}

int main() {

    if (fileIO) { setIO(); }

    string str;
    getline(cin, str);
    
    int dir = 0;
    int x = 0, y = 0;

    static bool visited[2000][2000];
    memset(visited, false, sizeof(visited));
    visited[1000][1000] = true;

    while (str.find(",") != string::npos) {

        bool left = str[0] == 'L';
        int amount = stoi(str.substr(1, str.find(",") - 1));

        if (left) { dir++; }
        else { dir--; }
        if (dir < 0) { dir = 3; }
        dir %= 4;

        if (dir == 0) {
            y += amount;
            for (int i = y - amount + 1; i <= y; i++) {
                if (visited[x + 1000][i + 1000]) {
                    printf("part 2: %d\n", abs(x) + abs(i));
                }
                else {
                    visited[x + 1000][i + 1000] = true;
                }
            }
        }
        if (dir == 1) {
            x += amount;
            for (int i = x - amount + 1; i <= x; i++) {
                if (visited[i + 1000][y + 1000]) {
                    printf("part 2: %d\n", abs(i) + abs(y));
                }
                else {
                    visited[i + 1000][y + 1000] = true;
                }
            }
        }
        if (dir == 2) {
            y -= amount;
            for (int i = y; i < y + amount; i++) {
                if (visited[x + 1000][i + 1000]) {
                    printf("part 2: %d\n", abs(x) + abs(i));
                }
                else {
                    visited[x + 1000][i + 1000] = true;
                }
            }
        }
        if (dir == 3) {
            x -= amount;
            for (int i = x; i < x + amount; i++) {
                if (visited[i + 1000][y + 1000]) {
                    printf("part 2: %d\n", abs(i) + abs(y));
                }
                else {
                    visited[i + 1000][y + 1000] = true;
                }
            }
        }

        str.erase(0, str.find(",") + 2);

    }

    printf("part 1: %d\n", abs(x) + abs(y));

}