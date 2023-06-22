#include <bits\stdc++.h>
using namespace std;

const bool fileIO = true;
void setIO() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
}

int main() {

    if (fileIO) { setIO(); }

    vector<vector<string>> input;
    for (int i = 0; i < 231; i++) {
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

    map<int, vector<int>> bots;
    map<int, vector<int>> output;
    while (input.size() > 0) {
        for (int i = input.size() - 1; i >= 0; i--) {
            if (input[i][0] == "value") {
                bots[stoi(input[i][5])].push_back(stoi(input[i][1]));
                input.erase(input.begin() + i);
            }
            else {
                auto it = bots.find(stoi(input[i][1]));
                if (it != bots.end() && it->second.size() == 2) {
                    int low = min(it->second[0], it->second[1]);
                    int high = max(it->second[0], it->second[1]);
                    
                    if (low == 17 && high == 61) {
                        cout << "part 1: " << input[i][1] << endl;
                    }

                    if (input[i][5] == "bot") {
                        bots[stoi(input[i][6])].push_back(low);
                    }
                    else {
                        output[stoi(input[i][6])].push_back(low);
                    }

                    if (input[i][10] == "bot") {
                        bots[stoi(input[i][11])].push_back(high);
                    }
                    else {
                        output[stoi(input[i][11])].push_back(high);
                    }
                    input.erase(input.begin() + i);
                }
            }
        }
    }

    cout << "part 2: " << output[0][0] * output[1][0] * output[2][0];

}