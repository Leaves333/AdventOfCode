#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
	fstream fin("input.txt");
	string str; fin >> str;
	vector<int> ids;
	for (int i = 0; i < str.size(); i++) {
		int val = str[i] - '0';
		if (i % 2 == 0) {
			for (int j = 0; j < val; j++) {
				ids.push_back(i / 2);
			}
		} else {
			for (int j = 0; j < val; j++) {
				ids.push_back(-1);
			}
		}
	}

	int left = 0, right = ids.size() - 1;
	while (left < right) {
		while (ids[left] != -1) {
			left++;
		}
		while (ids[right] == -1) {
			right--;
		}
		if (left >= right) break;
		ids[left] = ids[right];
		ids[right] = -1;
	}

	ll ans = 0;
	for (int i = 0; i < ids.size(); i++) {
		if (ids[i] != -1) {
			ans += i * ids[i];
		}
	}
	cout << "part 1: " << ans << endl;

	// do part 2, rebuild initial file system
	ids.clear();
	for (int i = 0; i < str.size(); i++) {
		int val = str[i] - '0';
		if (i % 2 == 0) {
			for (int j = 0; j < val; j++) {
				ids.push_back(i / 2);
			}
		} else {
			for (int j = 0; j < val; j++) {
				ids.push_back(-1);
			}
		}
	}

	for (int target_id = str.size() / 2; target_id >= 0; target_id--) {

		// find position and size of the target chunk
		int target_size = 0, target_pos = -1;
		for (int i = 0; i < ids.size(); i++) {
			if (ids[i] == target_id) {
				if (target_pos == -1) {
					target_pos = i;
				}
				target_size++;
			} else {
				if (target_pos != -1) {
					break;
				}
			}
		}

		// find position and size of a set of 0s
		int empty_size = 0, empty_pos = -1;
		for (int i = 0; i <= target_pos; i++) {
			if (empty_size >= target_size) {
				empty_pos = i - empty_size;
				break;
			}
			if (ids[i] == -1) {
				empty_size++;
			} else {
				empty_size = 0;
			}
		}

		if (empty_pos != -1) {
			for (int i = 0; i < target_size; i++) {
				ids[empty_pos + i] = target_id;
				ids[target_pos + i] = -1;
			}
		}

	}

	ans = 0;
	for (int i = 0; i < ids.size(); i++) {
		if (ids[i] != -1) {
			ans += i * ids[i];
		}
	}
	cout << "part 2: " << ans << endl;

}
