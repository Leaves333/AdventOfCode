#include <bits\stdc++.h>
using namespace std;

const bool fileIO = true;
void setIO() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
}

int minDistance = INT_MAX;
int maxDistance = INT_MIN;
map<string, vector<pair<string, int>>> paths;

void dfs(string loc, map<string, bool> visited, int dist) {

    bool visitedNew = false;
    //printf("visiting %s, dist=%d\n", loc.c_str(), dist);

    visited[loc] = true;
    for (auto path : paths[loc]) {
        if (!visited[path.first]) {
            dfs(path.first, visited, dist + path.second);
            visitedNew = true;
        }
    }
    visited[loc] = false;

    if (!visitedNew && dist < minDistance) {
        minDistance = dist;
    }

    if (!visitedNew && dist > maxDistance) {
        maxDistance = dist;
    }

}

int main() {

    if (fileIO) { setIO(); }

    for (int i = 0; i < 28; i++) {
        string start; cin >> start;
        string end; cin >> end >> end;
        string tmp; cin >> tmp >> tmp;
        int distance = stoi(tmp);
        paths[start].push_back(make_pair(end, distance));
        paths[end].push_back(make_pair(start, distance));
    }

    for (auto a : paths) {
        dfs(a.first, map<string, bool>(), 0);
        //cout << endl;
    }

    printf("min: %d\nmax: %d", minDistance, maxDistance);

}