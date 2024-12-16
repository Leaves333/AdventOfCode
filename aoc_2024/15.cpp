#include <bits/stdc++.h>
#include <utility>
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

pii wide_push(int x, int y, int *direction, vector<string> &grid) {

    // dfs for all the boxes...
    // find the ones most at the end for each coord...
    // check that we can push all them
    // if so... profit!!!
    // if else... do not profit

    // can't move at all
    if (grid[x + direction[0]][y + direction[1]] == '#') {
        return make_pair(x, y);
    }

    stack<pii> s;
    set<pii> visited;
    map<int, pii> boxes_on_edge;
    if (grid[x + direction[0]][y + direction[1]] != '.') {
        s.push(make_pair(x + direction[0], x + direction[1]));
    }

    bool can_push = false;
    while (!s.empty()) {

        // get the thing off the stack
        auto top = s.top();
        s.pop();
        visited.insert(top);

        // check if this is part of a box
        if (grid[top.first][top.first] == '[' &&
            !visited.count(make_pair(top.first, top.second + 1))) {
            s.push(make_pair(top.first, top.second + 1));
        }
        if (grid[top.first][top.first] == ']' &&
            !visited.count(make_pair(top.first, top.second - 1))) {
            s.push(make_pair(top.first, top.second - 1));
        }

        // check if this is the last box
    }

    // check if all the boxes on the edge are pushable
    for (const auto [key, val] : boxes_on_edge) {
    }

    if (can_push)
        return make_pair(x + direction[0], y + direction[1]);
    else
        return make_pair(x, y);
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
        string s;
        fin >> s;
        if (s[0] != '#') {
            instructions.push_back(s);
            break;
        }
        grid.push_back(s);
    }

    while (true) {
        string s;
        fin >> s;
        if (fin.eof())
            break;
        instructions.push_back(s);
    }

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

    pii normal_position;
    for (int x = 0; x < grid.size(); x++) {
        for (int y = 0; y < grid[0].size(); y++) {
            if (grid[x][y] == '@') {
                normal_position = make_pair(x, y);
                break;
            }
        }
    }

    pii wide_position;
    for (int x = 0; x < wide_grid.size(); x++) {
        for (int y = 0; y < wide_grid[0].size(); y++) {
            if (grid[x][y] == '@') {
                wide_position = make_pair(x, y);
                break;
            }
        }
    }

    int changes[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    for (string s : instructions) {
        for (char c : s) {
            switch (c) {
            case 'v':
                normal_position =
                    push(normal_position.first, normal_position.second,
                         changes[0], grid);
                break;
            case '^':
                normal_position =
                    push(normal_position.first, normal_position.second,
                         changes[1], grid);
                break;
            case '>':
                normal_position =
                    push(normal_position.first, normal_position.second,
                         changes[2], grid);
                break;
            case '<':
                normal_position =
                    push(normal_position.first, normal_position.second,
                         changes[3], grid);
                break;
            }
        }
        print_grid(wide_grid);
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

    ll part_2 = 0;
    for (int i = 0; i < wide_grid.size(); i++) {
        for (int j = 0; j < wide_grid.size(); j++) {
            if (wide_grid[i][j] == 'O') {
                part_2 += 100 * i + j;
            }
        }
    }
    cout << "part 2: " << part_2 << endl;
}
