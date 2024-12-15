#include <bits/stdc++.h>
#include <iterator>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

bool in_bounds(int x, int y, vector<string> &garden) {
    return x >= 0 && y >= 0 && x < garden.size() && y < garden[0].size();
}

int num_corners(int x, int y, vector<string> &garden) {

    int changes[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    int corner_changes[4][2] = {{1, 1}, {-1, 1}, {-1, -1}, {1, -1}};
    int corners = 0;

    int outside = 0, inside = 0;

    for (int i = 0; i < 4; i++) {
        auto first = changes[i];
        auto second = changes[(i + 1) % 4];
        auto third = corner_changes[i];

        // count outside corners...
        int diff_adj = 0;
        if (!in_bounds(x + first[0], y + first[1], garden)) {
            diff_adj++;
        } else if (garden[x + first[0]][y + first[1]] != garden[x][y]) {
            diff_adj++;
        }
        if (!in_bounds(x + second[0], y + second[1], garden)) {
            diff_adj++;
        } else if (garden[x + second[0]][y + second[1]] != garden[x][y]) {
            diff_adj++;
        }
        corners += (diff_adj == 2);
        outside += (diff_adj == 2);

        // count inside corners...
        bool diff_corner = false;
        if (in_bounds(x + third[0], y + third[1], garden) &&
            garden[x + third[0]][y + third[1]] != garden[x][y]) {
            diff_corner = true;
        }
        corners += ((diff_adj == 0) && diff_corner);
        inside += ((diff_adj == 0) && diff_corner);
    }

    /*cout << "corners at " << x << ", " << y << ": " << corners << endl;*/
    /*cout << "outside -> " << outside << ", inside -> " << inside << endl;*/
    return corners;
}

void dfs(int x, int y, int &area, int &perimeter, int &corners,
         set<pii> &visited, vector<string> &garden) {

    visited.insert(make_pair(x, y));
    corners += num_corners(x, y, garden);
    area++;

    // dfs to adj squares
    int changes[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    for (auto c : changes) {
        int new_x = x + c[0];
        int new_y = y + c[1];

        if (!in_bounds(new_x, new_y, garden)) {
            perimeter++;
        } else if (garden[new_x][new_y] != garden[x][y]) {
            perimeter++;
        } else if (visited.count(make_pair(new_x, new_y))) {
            continue;
        } else {
            dfs(new_x, new_y, area, perimeter, corners, visited, garden);
        }
    }
}

int main() {
    fstream fin("input.txt");
    vector<string> garden;
    while (true) {
        string s;
        fin >> s;
        if (fin.eof())
            break;
        garden.push_back(s);
    }

    set<pii> visited;
    ll part_1 = 0, part_2 = 0;
    for (int i = 0; i < garden.size(); i++) {
        for (int j = 0; j < garden[0].size(); j++) {
            if (visited.count(make_pair(i, j)))
                continue;
            int area = 0, perimeter = 0, corners = 0;
            dfs(i, j, area, perimeter, corners, visited, garden);

            cout << area << " " << corners << endl;
            part_1 += ((ll)area) * perimeter;
            part_2 += ((ll)area) * corners;
        }
    }

    cout << "part 1: " << part_1 << endl;
    cout << "part 2: " << part_2 << endl;

    // count corners for part 2:
    // number of sides = number of corners???
    // a corner is if X is surrounded on two sides by .
    // or if . is surrounded on two sides by X
    // .A XA
    // AX XX
}
