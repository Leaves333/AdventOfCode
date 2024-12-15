#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
typedef long long ll;

pii push(int x, int y, int *direction, vector<string> &grid) {
    
    // check if the first thing it finds is empty space or #
    int cur_x = x, cur_y = y;
    while (grid[cur_x][cur_y] == '@' || grid[cur_x][cur_y] == 'O') {
        cur_x += direction[0];
        cur_y += direction[1];
    }

    // can't push blocks
    if (grid[cur_x][cur_y] == '#') {
        return make_pair(x, y);
    }

    // move blocks
    while (cur_x != x || cur_y != y) {
        grid[cur_x][cur_y] = grid[cur_x - direction[0]][cur_y - direction[1]];
        cur_x -= direction[0];
        cur_y -= direction[1];
    }
    grid[cur_x][cur_y] = '.';
    return make_pair(x + direction[0], y + direction[1]);

}

pii push_wide(int x, int y, int *direction, vector<string> &grid) {
    
    // check if the first thing it finds is empty space or #
    int cur_x = x, cur_y = y;
    while (grid[cur_x][cur_y] == '@' || grid[cur_x][cur_y] == 'O') {
        cur_x += direction[0];
        cur_y += direction[1];
    }

    // can't push blocks
    if (grid[cur_x][cur_y] == '#') {
        return make_pair(x, y);
    }

    // move blocks
    while (cur_x != x || cur_y != y) {
        grid[cur_x][cur_y] = grid[cur_x - direction[0]][cur_y - direction[1]];
        cur_x -= direction[0];
        cur_y -= direction[1];
    }
    grid[cur_x][cur_y] = '.';
    return make_pair(x + direction[0], y + direction[1]);

}

void print_grid(vector<string> &grid) {
    for (string row : grid) {
        cout << row << endl;
    }
    cout << endl;
}

int main() {

    fstream fin("input.txt");
    vector<string> grid;
    vector<string> instructions;
    while (true) {
        string s; fin >> s;
        if (s[0] != '#') {
            instructions.push_back(s);
            break;
        }
        grid.push_back(s);
    }

    while (true) {
        string s; fin >> s;
        if (fin.eof()) break;
        instructions.push_back(s);
    }

    pii cur_position;
    for (int x = 0; x < grid.size(); x++) {
        for (int y = 0; y < grid[0].size(); y++) {
            if (grid[x][y] == '@') {
                cur_position = make_pair(x, y);
                break;
            }
        }
    }

    int changes[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    for (string s : instructions) {
        for (char c : s) {
            switch (c) {
                case 'v':
                    cur_position = push(cur_position.first, cur_position.second, changes[0], grid);
                break;
                case '^':
                    cur_position = push(cur_position.first, cur_position.second, changes[1], grid);
                break;
                case '>':
                    cur_position = push(cur_position.first, cur_position.second, changes[2], grid);
                break;
                case '<':
                    cur_position = push(cur_position.first, cur_position.second, changes[3], grid);
                break;
            }
        }
    }

    ll part_1 = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid.size(); j++) {
            if (grid[i][j] == 'O') {
                part_1 += 100 * i + j;
            }
        }
    }
    cout << "part 1: " << part_1 << endl;

    vector<string> wide_grid;
    for (string s : grid) {
        string row = "";
        for (char c : s) {
            switch (c) {
                case '#':
                    row += "##";
                break;
                case 'O':
                    row += "[]";
                break;
                case '.':
                    row += "..";
                break;
                case '@':
                    row += "@.";
                break;
            }
        }
    }

}
