#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

bool in_bounds(int x, int y, vector<string>& garden) {
	return x >= 0 && y >= 0 && x < garden.size() && y < garden[0].size();
}

// fix this func!!!
int num_corners(int x, int y, char plant_type, vector<string>& garden) {

	int changes[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
	int corners = 0;

	// looking for outside corners...
	if (garden[x][y] == plant_type) {
		for (int i = 0; i < 4; i++) {
			int borders;
			auto first = changes[i % 4];
			auto second = changes[(i + 1) % 4];
			if (!in_bounds(x + first[0], y + first[1], garden)) {
				borders++;
			} else if (garden[x + first[0]][y + first[1]] != plant_type) {
				borders++;
			}
			if (!in_bounds(x + second[0], y + second[1], garden)) {
				borders++;
			} else if (garden[x + second[0]][y + second[1]] != plant_type) {
				borders++;
			}
			corners += (borders == 2);
		}
		return corners;
	
	// looking for inside corners...
	} else {
		for (int i = 0; i < 4; i++) {
			int borders;
			auto first = changes[i % 4];
			auto second = changes[(i + 1) % 4];
			if (!in_bounds(x + first[0], y + first[1], garden)) {
				continue;
			} else if (garden[x + first[0]][y + first[1]] == plant_type) {
				borders++;
			}
			if (!in_bounds(x + second[0], y + second[1], garden)) {
				continue;
			} else if (garden[x + second[0]][y + second[1]] == plant_type) {
				borders++;
			}
			corners += (borders == 2);
		}
		return corners;
	}
}

void dfs(int x, int y, int& area, int& perimeter, int& corners, set<pii>& visited, vector<string> &garden) {
	visited.insert(make_pair(x, y));
	area++;
	int changes[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
	for (auto c : changes) {
		int new_x = x + c[0];
		int new_y = y + c[1];

		// count outside corners...
		corners += num_corners(x, y, garden[x][y], garden);

		if (!in_bounds(new_x, new_y, garden)) {
			perimeter++;
		} else if (garden[new_x][new_y] != garden[x][y]) {
			perimeter++;
			// count inside corners...
			corners += num_corners(new_x, new_y, garden[x][y], garden);
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
		if (fin.eof()) break;
		garden.push_back(s);
	}

	set<pii> visited;
	ll part_1 = 0, part_2 = 0;
	for (int i = 0; i < garden.size(); i++) {
		for (int j = 0; j < garden[0].size(); j++) {
			if (visited.count(make_pair(i, j))) continue;
			int area = 0, perimeter = 0, corners = 0;
			dfs(i, j, area, perimeter, corners, visited, garden);

			cout << area << " " << corners << endl;
			part_1 += ((ll) area) * perimeter;
			part_2 += ((ll) area) * corners;
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
