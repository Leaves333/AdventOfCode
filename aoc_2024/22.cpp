#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef long long ll;
typedef tuple<int, int, int, int> changes;

const int MOD = 16777216;

string stringify(changes c) {
    const auto [first, second, third, fourth] = c;
    return to_string(first) + ", " + to_string(second) + ", " +
           to_string(third) + ", " + to_string(fourth);
}

changes push(changes c, int x) {
    const auto [first, second, third, fourth] = c;
    return {second, third, fourth, x};
}

int main() {

    fstream fin("input.txt");
    vi nums;
    while (true) {
        int x;
        fin >> x;
        if (fin.eof())
            break;
        nums.push_back(x);
    }

    ll part_1 = 0;
    vector<vi> prices;
    for (int x : nums) {
        unsigned int cur = x;
        vi cur_prices;
        cur_prices.push_back(cur % 10);
        for (int i = 0; i < 2000; i++) {
            cur ^= (cur * 64);
            cur %= MOD;
            cur ^= (cur / 32);
            cur %= MOD;
            cur ^= (cur * 2048);
            cur %= MOD;
            cur_prices.push_back(cur % 10);
        }
        part_1 += cur;
        prices.push_back(cur_prices);
    }

    cout << "part 1: " << part_1 << endl;

    map<changes, int> profit; // map changes to total profit made
    for (auto p : prices) {
        changes cur_changes;
        set<changes> seen_changes;
        for (int i = 0; i < 2000; i++) {
            int diff = p[i + 1] - p[i];
            cur_changes = push(cur_changes, diff);
            if (i >= 3 && !seen_changes.count(cur_changes)) {
                seen_changes.insert(cur_changes);
                profit[cur_changes] += p[i + 1];
            }
        }
    }

    changes best_key;
    int best_profit = 0;
    for (const auto &[key, value] : profit) {
        if (value > best_profit) {
            best_profit = value;
            best_key = key;
        }
    }
    cout << "best key: " << stringify(best_key) << ", profit=" << best_profit << endl;

}
