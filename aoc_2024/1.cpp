#include <bits/stdc++.h>
using namespace std;

int main() {
	fstream fin("input.txt");
	vector<int> x, y;
	map<int, int> m, n;
	while (true) {
		int a, b;
		fin >> a >> b;
		if (fin.eof()) break;
		x.push_back(a);
		y.push_back(b);
		m[a]++;
		n[b]++;
	}

	sort(x.begin(), x.end());
	sort(y.begin(), y.end());
	int ans = 0;
	for (int i = 0; i < x.size(); i++) {
		ans += abs(x[i] - y[i]);
	}
	cout << "part 1: " << ans << endl;

	ans = 0;
	for (auto const& [key, value] : m) {
		ans += key * value * n[key];
	}

	cout << "part 2: " << ans << endl;
}
