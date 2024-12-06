#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

bool gets_stuck(vector<string>& grid, int x, int y) {
	int steps = 0, max_steps = grid.size() * grid[0].size() * 2;
	int direction = 0; // 0=up, 1=right, 2=down, 3=left
	while (x >= 0 && y >= 0 && x < grid.size() && y < grid[0].size() && steps < max_steps) {
		int dx = 0, dy = 0;
		switch (direction % 4) {
			case 0:
				dx = -1;
				break;
			case 1:
				dy = 1;
				break;
			case 2:
				dx = 1;
				break;
			case 3:
				dy = -1;
				break;
		}

		int new_x = x + dx, new_y = y + dy;
		if (!(new_x >= 0 && new_y >= 0 && new_x < grid.size() && new_y < grid[0].size())) {
			break;
		}
		if (grid[new_x][new_y] == '#') {
			direction++;
			continue;
		}

		x = new_x;
		y = new_y;
		steps++;
	}

	return steps == max_steps;
}

int main() {

	fstream fin("input.txt");
	vector<string> grid;
	while (true) {
		string s;
		fin >> s;
		if (fin.eof()) break;
		grid.push_back(s);
	}

	int starting_x, starting_y;
	for (int i = 0; i < grid.size(); i++) {
		for (int j = 0; j < grid[0].size(); j++) {
			if (grid[i][j] == '^') {
				starting_x = i; starting_y = j;
			}
		}
	}

	vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));
	int x = starting_x, y = starting_y;
	int direction = 0; // 0=up, 1=right, 2=down, 3=left
	while (x >= 0 && y >= 0 && x < grid.size() && y < grid[0].size()) {
		visited[x][y] = true;
		int dx = 0, dy = 0;
		switch (direction % 4) {
			case 0:
				dx = -1;
				break;
			case 1:
				dy = 1;
				break;
			case 2:
				dx = 1;
				break;
			case 3:
				dy = -1;
				break;
		}

		int new_x = x + dx, new_y = y + dy;
		if (!(new_x >= 0 && new_y >= 0 && new_x < grid.size() && new_y < grid[0].size())) {
			break;
		}
		if (grid[new_x][new_y] == '#') {
			direction++;
			continue;
		}

		x = new_x;
		y = new_y;
	}

	int part_1 = 0;
	for (int i = 0; i < visited.size(); i++) {
		for (int j = 0; j < visited[0].size(); j++) {
			part_1 += visited[i][j];
		}
	}

	cout << "part 1: " << part_1 << endl;

	int part_2 = 0;
	for (int i = 0; i < grid.size(); i++) {
		for (int j = 0; j < grid[0].size(); j++) {
			if (grid[i][j] != '.') continue;
			grid[i][j] = '#';
			/*cout << i << " , " << j << " -> " <<  gets_stuck(grid, starting_x, starting_y) << endl;*/
			part_2 += gets_stuck(grid, starting_x, starting_y);
			grid[i][j] = '.';
		}
	}

	cout << "part 2: " << part_2 << endl;

}
