#include <bits\stdc++.h>
using namespace std;

const bool fileIO = true;
void setIO() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
}

int main() {

    if (fileIO) { setIO(); }

    map<char, int> frequency[8];
    for (int i = 0; i < 624; i++) {
        string str; cin >> str;
        for (int j = 0; j < str.length(); j++) {
            frequency[j][str[j]]++;
        }
    }

    string ans = "";
    string leastAns = "";
    for (map<char, int> &m : frequency) {
        char mostCommon = ' ';
        int most = 0;
        char leastCommon = ' ';
        int least = 1000;
        for (auto &a : m) {
            if (a.second > most) {
                mostCommon = a.first;
                most = a.second;
            }
            if (a.second < least) {
                leastCommon = a.first;
                least = a.second;
            }
        }
        ans += mostCommon;
        leastAns += leastCommon;
    }

    cout << ans << endl << leastAns;

}