#include <bits/stdc++.h>
using namespace std;

bool in_bounds(int i, int j, vector<string> grid) {
	return i >= 0 && j >= 0 && i < grid.size() && j < grid.size();
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

	int part_1 = 0;

	// horizontal
	for (int i = 0; i < grid.size(); i++) {
		// forwards
		string cur_str = "";
		for (int j = 0; j < grid.size(); j++) {
			cur_str += grid[i][j];
			if (cur_str == "XMAS") {
				part_1++;
			}
			if (cur_str.length() >= 4) {
				cur_str = cur_str.substr(1);
			}
		}

		// backwards
		cur_str = "";
		for (int j = grid.size() - 1; j >= 0; j--) {
			cur_str += grid[i][j];
			if (cur_str == "XMAS") {
				part_1++;
			}
			if (cur_str.length() >= 4) {
				cur_str = cur_str.substr(1);
			}
		}
	}

	// vertical 
	for (int i = 0; i < grid.size(); i++) {

		// down
		string cur_str = "";
		for (int j = 0; j < grid.size(); j++) {
			cur_str += grid[j][i];
			if (cur_str == "XMAS") {
				part_1++;
			}
			if (cur_str.length() >= 4) {
				cur_str = cur_str.substr(1);
			}
		}

		// up
		cur_str = "";
		for (int j = grid.size() - 1; j >= 0; j--) {
			cur_str += grid[j][i];
			if (cur_str == "XMAS") {
				part_1++;
			}
			if (cur_str.length() >= 4) {
				cur_str = cur_str.substr(1);
			}
		}
	}

	// i+j=x
	for (int x = 0; x <= grid.size() * 2; x++) {
		
		string cur_str = "";
		for (int i = 0; i < grid.size(); i++) {
			int j = x - i;
			if (!in_bounds(i, j, grid)) continue;
			cur_str += grid[i][j];
			if (cur_str == "XMAS") {
				part_1++;
			}
			if (cur_str.length() >= 4) {
				cur_str = cur_str.substr(1);
			}
		}

		cur_str = "";
		for (int i = grid.size(); i >= 0; i--) {
			int j = x - i;
			if (!in_bounds(i, j, grid)) continue;
			cur_str += grid[i][j];
			if (cur_str == "XMAS") {
				part_1++;
			}
			if (cur_str.length() >= 4) {
				cur_str = cur_str.substr(1);
			}
		}

	}

	for (int x = -1 * grid.size(); x <= (int) grid.size(); x++) {

		string cur_str = "";
		for (int i = 0; i < grid.size(); i++) {
			int j = i - x;
			if (!in_bounds(i, j, grid)) continue;
			cur_str += grid[i][j];
			if (cur_str == "XMAS") {
				part_1++;
			}
			if (cur_str.length() >= 4) {
				cur_str = cur_str.substr(1);
			}
		}

		cur_str = "";
		for (int i = grid.size(); i >= 0; i--) {
			int j = i - x;
			if (!in_bounds(i, j, grid)) continue;
			cur_str += grid[i][j];
			if (cur_str == "XMAS") {
				part_1++;
			}
			if (cur_str.length() >= 4) {
				cur_str = cur_str.substr(1);
			}
		}

	}

	cout << "part 1: " << part_1 << endl;

	int part_2 = 0;
	for (int i = 1; i < grid.size() - 1; i++) {
		for (int j = 1; j < grid.size() - 1; j++) {
			if (grid[i][j] != 'A') continue;
			string corners = "";
			corners += grid[i - 1][j - 1];
			corners += grid[i - 1][j + 1];
			corners += grid[i + 1][j + 1];
			corners += grid[i + 1][j - 1];
			const string valid_strings[4] = {"MMSS", "SMMS", "SSMM", "MSSM"};
			for (auto str : valid_strings) {
				if (str == corners) {
					part_2++;
					break;
				}
			}
		}
	}

	cout << "part 2: " << part_2 << endl;

}
