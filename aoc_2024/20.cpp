#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
typedef vector<int> vi;

const int TIME_SAVED_THRESHOLD = 100;

// checks if x, y is on an empty square
bool in_bounds(int x, int y, vector<string> &grid) {
    if (x < 0 || y < 0 || x >= grid.size() || y >= grid[0].size()) {
        return false;
    }
    return grid[x][y] != '#';
}

int main() {

    // read input
    fstream fin("input.txt");
    vector<string> grid;
    while (true) {
        string s;
        fin >> s;
        if (fin.eof())
            break;
        grid.push_back(s);
    }

    // find starting and ending points
    pii start, end;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == 'S') {
                start = make_pair(i, j);
            }
            if (grid[i][j] == 'E') {
                end = make_pair(i, j);
            }
        }
    }

    // calculate distance from start and end
    vector<vi> dist_from_start(grid.size(), vi(grid[0].size(), INT_MAX));
    vector<vi> dist_from_end(grid.size(), vi(grid[0].size(), INT_MAX));
    dist_from_start[start.first][start.second] = 0;
    dist_from_end[end.first][end.second] = 0;

    // calculate distance from start
    priority_queue<pair<int, pii>> pq;
    pq.push(make_pair(0, start));
    while (!pq.empty()) {
        int cur_dist = -1 * pq.top().first;
        int x = pq.top().second.first;
        int y = pq.top().second.second;
        pq.pop();

        const int ADJACENT_CELLS[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        for (auto c : ADJACENT_CELLS) {
            int new_x = x + c[0];
            int new_y = y + c[1];
            if (!in_bounds(new_x, new_y, grid)) {
                continue;
            }
            if (dist_from_start[new_x][new_y] <= cur_dist + 1) {
                continue;
            }
            dist_from_start[new_x][new_y] = cur_dist + 1;
            pq.push(make_pair(-1 * (cur_dist + 1), make_pair(new_x, new_y)));
        }
    }

    // calculate distance from end
    pq.push(make_pair(0, end));
    while (!pq.empty()) {
        int cur_dist = -1 * pq.top().first;
        int x = pq.top().second.first;
        int y = pq.top().second.second;
        pq.pop();

        const int ADJACENT_CELLS[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        for (auto c : ADJACENT_CELLS) {
            int new_x = x + c[0];
            int new_y = y + c[1];
            if (!in_bounds(new_x, new_y, grid)) {
                continue;
            }
            if (dist_from_end[new_x][new_y] <= cur_dist + 1) {
                continue;
            }
            dist_from_end[new_x][new_y] = cur_dist + 1;
            pq.push(make_pair(-1 * (cur_dist + 1), make_pair(new_x, new_y)));
        }
    }

    // solve the problem
    int part_1 = 0, part_2 = 0;
    set<pair<pii, pii>> skips_seen;
    for (int x = 0; x < grid.size(); x++) {
        for (int y = 0; y < grid[0].size(); y++) {

            if (!in_bounds(x, y, grid))
                continue;

            for (int dx = -20; dx <= 20; dx++) {
                for (int dy = -20; dy <= 20; dy++) {

                    int new_x = x + dx;
                    int new_y = y + dy;
                    if (!in_bounds(new_x, new_y, grid))
                        continue;

                    pair<pii, pii> cur_skip =
                        make_pair(make_pair(x, y), make_pair(new_x, new_y));
                    if (skips_seen.count(cur_skip))
                        continue;
                    skips_seen.insert(cur_skip);

                    int manhattan_dist = abs(dx) + abs(dy);
                    int time_after_skip = dist_from_start[x][y] +
                                          dist_from_end[new_x][new_y] +
                                          manhattan_dist;
                    if (time_after_skip + TIME_SAVED_THRESHOLD >
                        dist_from_start[end.first][end.second])
                        continue;

                    if (manhattan_dist <= 20)
                        part_2++;
                    if (manhattan_dist <= 2)
                        part_1++;
                }
            }
        }
    }

    cout << "part 1: " << part_1 << endl;
    cout << "part 2: " << part_2 << endl;
}
