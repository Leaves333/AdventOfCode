#include <bits\stdc++.h>
using namespace std;

const bool fileIO = true;
void setIO() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
}

int main() {

    if (fileIO) { setIO(); }
    const string letters = "abcd";

    map<string, int> reg;
    reg["a"] = 0; reg["b"] = 0; reg["c"] = 1; reg["d"] = 0;
    vector<vector<string>> input;

    for (int i = 0; i < 23; i++) {
        string str;
        getline(cin, str);
        vector<string> cur;
        while (str.find(" ") != string::npos) {
            cur.push_back(str.substr(0, str.find(" ")));
            str.erase(0, str.find(" ") + 1);
        }
        cur.push_back(str);
        input.push_back(cur);
    }

    int i = 0;
    while (i < 23) {
        vector<string> cur = input[i];
        
        if (cur[0] == "cpy") {
            if (letters.find(cur[1]) != string::npos) {
                reg[cur[2]] = reg[cur[1]];
            }
            else {
                reg[cur[2]] = stoi(cur[1]);
            }
        }
        
        if (cur[0] == "inc") {
            reg[cur[1]]++;
        }
        
        if (cur[0] == "dec") {
            reg[cur[1]]--;
        }
        
        if (cur[0] == "jnz") {
            if (letters.find(cur[1]) != string::npos) {
                if (reg[cur[1]] != 0) {
                    i += stoi(cur[2]);
                }
                else {
                    i++;
                }
            }
            else {
                i += stoi(cur[2]);
            }
        }
        else {
            i++;
        }

    }

    cout << reg["a"];

}