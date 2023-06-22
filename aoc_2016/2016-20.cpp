#include <bits\stdc++.h>
using namespace std;

const bool fileIO = true;
void setIO() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
}

int main() {

    if (fileIO) { setIO(); }

    vector<pair<long long, long long>> filters;

    for (int i = 0; i < 945; i++) {
        string str; 
        cin >> str;
        string aaa = str.substr(str.find("-") + 1);
        long long a = stoll(str.substr(0, str.find("-")));
        long long b = stoll(str.substr(str.find("-") + 1));
        filters.push_back(make_pair(a, b));
    }

    bool found = false;
    long long ans = 0;
    while (!found) {
        found = true;
        for (auto p : filters) {
            if (p.first <= ans && p.second >= ans) {
                ans = p.second + 1;
                found = false;
            }
        }
    }

    cout << ans << endl;

    vector<pair<long long, long long>> ranges;
    ranges.push_back(make_pair(0, 4294967295));

    for (auto p : filters) {
        for (int i = ranges.size() - 1; i >= 0; i--) {
            auto r = ranges[i];
            if (r.first >= p.first && r.second <= p.second) {
                ranges.erase(ranges.begin() + i);
            }
            else if (r.first < p.first && r.second >= p.first && r.second <= p.second) {
                ranges[i].second = p.first - 1;
            }
            else if (r.first >= p.first && r.first <= p.second && r.second > p.second) {
                ranges[i].first = p.second + 1;
            }
            else if (r.first < p.first && r.second > p.second) {
                ranges.erase(ranges.begin() + i);
                ranges.push_back(make_pair(r.first, p.first - 1));
                ranges.push_back(make_pair(p.second + 1, r.second));
            }
        }
    }

    ans = 0;
    for (auto r : ranges) {
        ans += r.second - r.first + 1;
    }

    cout << ans;

}