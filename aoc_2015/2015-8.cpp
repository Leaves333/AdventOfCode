#include <bits\stdc++.h>
using namespace std;

const bool fileIO = true;
void setIO() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
}

int main() {

    if (fileIO) { setIO(); }

    int total = 0;
    int stored = 0;
    int doubled = 0;

    for (int i = 0; i < 300; i++) {
        string str; cin >> str;

        total += str.length();
        stored += str.length() - 2;
        //cout << str << endl;
        for (int j = 1; j < str.length() - 2; j++) {
            //cout << str.substr(i, 2) << endl;
            if (str.substr(j, 2) == "\\\\") { stored -= 1; j++; }
            else if (str.substr(j, 2) == "\\\"") { stored -= 1; j++; }
            else if (str.substr(j, 2) == "\\x") { stored -= 3; j += 3;  }
        }

        for (int j = 0; j < str.length(); j++) {
            if (str[j] == '\"' || str[j] == '\\') doubled++; 
        }
        doubled += 2;
        
    }

    cout << total - stored << endl;
    cout << doubled << endl;

}