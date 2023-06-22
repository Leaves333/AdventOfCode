#include <bits\stdc++.h>
using namespace std;

const bool fileIO = true;
void setIO() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
}

int main() {

    if (fileIO) { setIO(); }

    const int INPUT_SIZE = 46;
    map<string, long long> reg;
    reg["a"] = 1;
    reg["b"] = 0;

    vector<vector<string>> input;

    for (int i = 0; i < INPUT_SIZE; i++) {
        string str;
        getline(cin, str);

        vector<string> tmp;
        while (str.find(" ") != string::npos) {
            tmp.push_back(str.substr(0, str.find(" ")));
            str.erase(0, str.find(" ") + 1);
        }
        tmp.push_back(str);
        input.push_back(tmp);

    }

    for (int i = 0; i < INPUT_SIZE; i++) {

        vector<string> cur = input[i];

        if (cur[0] == "hlf") {
            reg[cur[1]] /= 2;
        }
        else if (cur[0] == "tpl") {
            reg[cur[1]] *= 3;
        }
        else if (cur[0] == "inc") {
            reg[cur[1]]++;
        }
        else if (cur[0] == "jmp") {
            i += stoi(cur[1]) - 1;
        }
        else if (cur[0] == "jie") {
            if (reg[cur[1].substr(0, 1)] % 2 == 0) {
                i += stoi(cur[2]) - 1;
            }
        }
        else if (cur[0] == "jio") {
            if (reg[cur[1].substr(0, 1)] == 1) {
                i += stoi(cur[2]) - 1;
            }
        }

    }

    cout << reg["b"];

}