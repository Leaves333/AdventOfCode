#include <bits\stdc++.h>
using namespace std;

const bool fileIO = true;
void setIO() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
}

int main() {

    if (fileIO) { setIO(); }

    string cur = "3113322113";
    //cout << cur << endl;
    for (int i = 0; i < 50; i++) {
        string tmp = "";
        int streak = 1;
        for (int j = 1; j < cur.length(); j++) {
            if (cur[j] == cur[j - 1]) { streak++; }
            else { tmp += to_string(streak) + cur[j - 1]; streak = 1; }
        }
        tmp += to_string(streak) + cur[cur.length() - 1];
        cur = tmp;
        //cout << cur << endl;
    }

    cout << cur.length() << endl;

}