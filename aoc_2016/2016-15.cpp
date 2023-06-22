#include <bits\stdc++.h>
using namespace std;

const bool fileIO = true;
void setIO() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
}

int main() {

    if (fileIO) { setIO(); }

    vector<pair<int, int>> discs; //positions, starting location
    for (int i = 0; i < 6; i++) {
        string str;
        getline(cin, str);
        vector<string> input;
        while (str.find(" ") != string::npos) {
            input.push_back(str.substr(0, str.find(" ")));
            str.erase(0, str.find(" ") + 1);
        }
        discs.push_back(make_pair(stoi(input[3]), stoi(str.substr(0, str.length() - 1))));
    }

    if (true) {
        discs.push_back(make_pair(11, 0));
    }

    int i = 0;
    while (true) {

        bool found = true;
        for (int k = 0; k < discs.size(); k++) {
            pair<int, int> cur = discs[k];
            if (i % cur.first != (cur.first - ((cur.second + k + 1) % cur.first)) % cur.first) {
                found = false;
                break;
            }
        }

        if (found) {
            break;
        }

        i++;
    }

    cout << i;

}