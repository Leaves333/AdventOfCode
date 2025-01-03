#include <bits/stdc++.h>
#include <utility>
#include <vector>
using namespace std;

typedef vector<int> vi;
typedef vector<vector<int>> vii;
typedef pair<int, int> pii;

struct location {
    int x;
    int y;
    int dir;

    location(int x, int y, int dir) : x(x), y(y), dir(dir) {}
    friend bool operator<(const location &l, const location &r) {
        return tie(l.x, l.y, l.dir) < tie(r.x, r.y, r.dir);
    }

    string str() {
        return "{x=" + to_string(x) + ", y=" + to_string(y) +
               ", dir=" + to_string(dir) + "}";
    }
};

int min_dist(int x, int y, const vector<vii> &dist) {
    int smol = INT_MAX;
    for (int i = 0; i < 4; i++) {
        smol = min(smol, dist[x][y][i]);
    }
    return smol;
}

int main() {

    // get input
    fstream fin("input.txt");
    vector<string> grid;
    while (true) {
        string s;
        fin >> s;
        if (fin.eof())
            break;
        grid.push_back(s);
    }

    // stores x, y, direction,
    // 0 = right, 1 = up, 2 = left, 3 = down
    vector<vii> dist =
        vector<vii>(grid.size(), vii(grid[0].size(), vi(4, INT_MAX)));
    dist[grid.size() - 2][1][0] = 0;

    // -dist, location, dist is negative bc max heap
    priority_queue<pair<int, location>> pq;
    pq.push(make_pair(0, location(grid.size() - 2, 1, 0)));

    // dijkstra's for best path
    const int changes[4][2] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};
    while (!pq.empty()) {
        location pos = pq.top().second;
        int cur_dist = pq.top().first * -1;
        pq.pop();

        // go straight...
        auto dir = changes[pos.dir];
        if (grid[pos.x + dir[0]][pos.y + dir[1]] != '#') {
            if (dist[pos.x + dir[0]][pos.y + dir[1]][pos.dir] > cur_dist + 1) {
                dist[pos.x + dir[0]][pos.y + dir[1]][pos.dir] = cur_dist + 1;
                pq.push(make_pair(
                    -1 * (cur_dist + 1),
                    location(pos.x + dir[0], pos.y + dir[1], pos.dir)));
            }
        }

        // try to turn...
        for (int i = (pos.dir + 1) % 2; i < 4; i += 2) {
            if (dist[pos.x][pos.y][i] > cur_dist + 1000) {
                dist[pos.x][pos.y][i] = cur_dist + 1000;
                pq.push(make_pair(-1 * (cur_dist + 1000),
                                  location(pos.x, pos.y, i)));
            }
        }
    }

    int part_1 = min_dist(1, grid[0].size() - 2, dist);
    cout << "part_1: " << part_1 << endl;

    // count number of cells on the best paths
    set<pii> seen;
    set<location> visited;
    queue<location> q;

    for (int i = 0; i < 4; i++) {
        visited.insert(location(2, grid[0].size() - 2, i));
        q.push(location(2, grid[i].size() - 2, i));
    }

    while (!q.empty()) {

        auto pos = q.front();
        q.pop();

        seen.insert(make_pair(pos.x, pos.y));

        // go backwards...
        auto dir = changes[pos.dir];
        if (grid[pos.x - dir[0]][pos.y - dir[1]] != '#') {
            bool decreasing_dist =
                dist[pos.x - dir[0]][pos.y - dir[1]][pos.dir] <
                dist[pos.x][pos.y][pos.dir];
            bool not_visited = !visited.count(
                location(pos.x - dir[0], pos.y - dir[1], pos.dir));

            auto next_dist = dist[pos.x - dir[0]][pos.y - dir[1]][pos.dir];
            auto cur_dist = dist[pos.x][pos.y][pos.dir];

            if (decreasing_dist && not_visited) {
                auto target_location =
                    location(pos.x - dir[0], pos.y - dir[1], pos.dir);
                q.push(target_location);
                visited.insert(target_location);
            }
        }

        // try to turn...
        for (int i = (pos.dir + 1) % 2; i < 4; i += 2) {
            // break if not less than
            if (dist[pos.x][pos.y][i] >= dist[pos.x][pos.y][pos.dir])
                continue;

            // break if already visited
            if (visited.count(location(pos.x, pos.y, i)))
                continue;

            // add location to queue
            auto target_location = location(pos.x, pos.y, i);
            q.push(target_location);
            visited.insert(target_location);
        }
    }

    cout << "part_2: " << seen.size() + 1 << endl;
}
