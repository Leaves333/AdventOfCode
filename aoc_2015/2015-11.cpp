#include <bits\stdc++.h>
using namespace std;

const bool fileIO = true;
void setIO() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
}

bool isValid(string str) {
    bool orderedLetter = false;
    int doubleLetters = 0;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == 'i' || str[i] == 'o' || str[i] == 'l') {
            return false;
        }
        if (i >= 2 && str[i] == str[i - 1] + 1 && str[i - 1] == str[i - 2] + 1) {
            orderedLetter = true;
        }
    }

    for (int i = 1; i < str.length(); i++) {
        if (str[i] == str[i - 1]) {
            doubleLetters++; i++;
        }
    }

    return doubleLetters >= 2 && orderedLetter;
}

int main() {

    if (fileIO) { setIO(); }

    string key = "hxbxxzaa";

    while (!isValid(key)) {
        int pos = 8;
        key[pos]++;
        while (key[pos] > 'z') {
            key[pos] = 'a';
            pos--;
            key[pos]++;
        }
    }

    cout << key << endl;

}