#include <bits/stdc++.h>
#include <utility>
using namespace std;

typedef pair<int, int> pii;

bool in_bound(int x, int y, vector<string> &grid) {
	return x >= 0 && y >= 0 && x < grid.size() && y < grid[0].size();
}

void dfs(int x, int y, vector<string> &grid, set<pii> &seen) {
	if (grid[x][y] == '9') {
		seen.insert(make_pair(x, y));
		return;
	}
	int changes[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
	for (auto c : changes) {
		int new_x = x + c[0];
		int new_y = y + c[1];
		if (!in_bound(new_x, new_y, grid)) continue;
		if (grid[new_x][new_y] == grid[x][y] + 1)
			dfs(new_x, new_y, grid, seen);
	}
}

int rating(int x, int y, vector<string> &grid) {
	if (grid[x][y] == '9') return 1;
	int val = 0;
	int changes[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
	for (auto c : changes) {
		int new_x = x + c[0];
		int new_y = y + c[1];
		if (!in_bound(new_x, new_y, grid)) continue;
		if (grid[new_x][new_y] == grid[x][y] + 1)
			val += rating(new_x, new_y, grid);
	}
	return val;
}

int main() {
	fstream fin("input.txt");
	vector<string> grid;
	while (true) {
		string line;
		fin >> line;
		if (fin.eof()) break;
		grid.push_back(line);
	}

	// dfs???
	int part_1 = 0;
	int part_2 = 0;
	for (int i = 0; i < grid.size(); i++) {
		for (int j = 0; j < grid.size(); j++) {
			if (grid[i][j] == '0') {
				set<pii> seen;
				dfs(i, j, grid, seen);
				part_1 += seen.size();
				part_2 += rating(i, j, grid);
			}
		}
	}

	cout << "part 1: " << part_1 << endl;
	cout << "part 2: " << part_2 << endl;
}
