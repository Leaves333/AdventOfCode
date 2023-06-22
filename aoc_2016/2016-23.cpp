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
    reg["a"] = 12; reg["b"] = 0; reg["c"] = 0; reg["d"] = 0;
    vector<vector<string>> input;

    const int INPUT_SIZE = 26;

    for (int i = 0; i < INPUT_SIZE; i++) {
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
    while (i < INPUT_SIZE) {

        vector<string> cur = input[i];

        if (cur[0] == "tgl") {

            int targetIndex = i;
            if (letters.find(cur[1]) != string::npos) {
                targetIndex += reg[cur[1]];
            }
            else {
                targetIndex += stoi(cur[1]);
            }

            if (targetIndex >= 0 && targetIndex < INPUT_SIZE) { //targets an instruction

                vector<string> &target = input[targetIndex];

                if (target.size() == 2) { // 1 argument
                    if (target[0] == "inc") {
                        target[0] = "dec";
                    }
                    else {
                        target[0] = "inc";
                    }
                }
                else if (target.size() == 3) { // 2 arguments
                    if (target[0] == "jnz") {
                        target[0] = "cpy";
                    }
                    else {
                        target[0] = "jnz";
                    }
                }

            }
        }
        
        if (cur[0] == "cpy") {
            if (letters.find(cur[1]) != string::npos) {
                reg[cur[2]] = reg[cur[1]];
            }
            else if (letters.find(cur[2]) != string::npos) {
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
                    if (letters.find(cur[2]) != string::npos) {
                        i += reg[cur[2]] - 1;
                    }
                    else {
                        i += stoi(cur[2]) - 1;
                    }
                }
            }
            else { //not a letter
                if (letters.find(cur[2]) != string::npos) {
                    i += reg[cur[2]] - 1;
                }
                else {
                    i += stoi(cur[2]) - 1;
                }
            }
        }

        i++;

    }

    cout << reg["a"];

}