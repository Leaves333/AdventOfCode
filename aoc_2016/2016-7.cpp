#include <bits\stdc++.h>
using namespace std;

const bool fileIO = true;
void setIO() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
}

int main() {

    if (fileIO) { setIO(); }

    int ans = 0;
    int anss = 0;
    for (int i = 0; i < 2000; i++) {

        string str; cin >> str;

        vector<string> normal, brackets;
        while (str.find("[") != string::npos) {
            normal.push_back(str.substr(0, str.find("[")));
            str.erase(0, str.find("[") + 1);
            brackets.push_back(str.substr(0, str.find("]")));
            str.erase(0, str.find("]") + 1);
        }
        normal.push_back(str);

        bool good = false;
        bool otherGood = false;

        vector<string> toMatch;
        for (string s : normal) {
            for (int k = 2; k < s.length() - 1; k++) {
                if (s[k] == s[k - 1] && s[k + 1] == s[k - 2] && s[k] != s[k + 1]) {
                    good = true;
                }
            }
            for (int k = 1; k < s.length() - 1; k++) {
                if (s[k + 1] == s[k - 1] && s[k] != s[k + 1]) {
                    string newStr = "";
                    newStr += s[k] ;
                    newStr += s[k - 1];
                    newStr += s[k];
                    toMatch.push_back(newStr);
                    //cout << newStr << endl;
                }
            }
        }
        for (string s : brackets) {
            for (int k = 2; k < s.length() - 1; k++) {
                if (s[k] == s[k - 1] && s[k + 1] == s[k - 2] && s[k] != s[k + 1]) {
                    good = false;
                }
            }
            for (int k = 0; k < s.length() - 2; k++) {
                string sub = s.substr(k, 3);
                for (string match : toMatch) {
                    if (sub == match) { otherGood = true; }
                }
            }
        }

        if (good) { 
            ans++; 
        }
        if (otherGood) {
            anss++;
        }

    }

    cout << ans << endl << anss;

}