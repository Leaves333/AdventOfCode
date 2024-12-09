#include <bits/stdc++.h>
#include <fstream>
#include <utility>
using namespace std;

typedef pair<int, int> pii;

bool in_bounds(const vector<string>& grid, pii loc) {
	return loc.first >= 0 && loc.second >= 0 && loc.first < grid.size() && loc.second < grid[0].size();
}

int main() {

	// grab input
	fstream fin("input.txt");
	vector<string> grid;
	while (true) {
		string line;
		fin >> line;
		if (fin.eof()) break;
		grid.push_back(line);
	}

	// group antennas by char
	map<char, vector<pii>> m;
	for (int i = 0; i < grid.size(); i++) {
		for (int j = 0; j < grid[0].length(); j++) {
			if (grid[i][j] != '.') {
				m[grid[i][j]].push_back(make_pair(i, j));
			}
		}
	}

	// calculate locations of antinodes
	// part 1
	set<pii> antinodes;
	for (const auto& [key, v] : m) {
		for (int i = 0; i < v.size(); i++) {
			for (int j = i + 1; j < v.size(); j++) {
				pii a = v[i], b = v[j];
				int dx = b.first - a.first, dy = b.second - a.second;
				pii m = make_pair(b.first + dx, b.second + dy);
				pii n = make_pair(a.first - dx, a.second - dy);
				if (in_bounds(grid, m)) { antinodes.insert(m); }
				if (in_bounds(grid, n)) { antinodes.insert(n); }
			}
		}
	}
	cout << "part 1: " << antinodes.size() << endl;

	antinodes.clear();
	for (const auto& [key, v] : m) {
		for (int i = 0; i < v.size(); i++) {
			for (int j = i + 1; j < v.size(); j++) {

				pii a = v[i], b = v[j];
				int dx = b.first - a.first, dy = b.second - a.second;
				pii start = make_pair(a.first, a.second);

				pii cur = start;
				while (in_bounds(grid, cur)) {
					antinodes.insert(cur);
					cur.first += dx;
					cur.second += dy;
				}

				cur = start;
				while (in_bounds(grid, cur)) {
					antinodes.insert(cur);
					cur.first -= dx;
					cur.second -= dy;
				}
			}
		}
	}
	cout << "part 2: " << antinodes.size() << endl;

}
