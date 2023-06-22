#include <bits\stdc++.h>
using namespace std;

const bool fileIO = true;
void setIO() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
}

int main() {

    if (fileIO) { setIO(); }

    string start = "10111100110001111";
    int diskLength = 35651584;

    string cur = start;
    while (cur.length() < diskLength) {
        string copy = "";
        for (int i = cur.length() - 1; i >= 0; i--) {
            if (cur[i] == '0') {
                copy += '1';
            }
            else {
                copy += '0';
            }
        }
        cur = cur + "0" + copy;
    }
    cur = cur.substr(0, diskLength);

    while (cur.length() % 2 == 0) {
        string checksum = "";
        for (int i = 0; i < cur.length() / 2; i++) {
            if (cur[i * 2] == cur[i * 2 + 1]) {
                checksum += "1";
            }
            else {
                checksum += "0";
            }
        }
        cur = checksum;
    }

    cout << cur;

}