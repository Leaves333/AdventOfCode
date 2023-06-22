#include <bits\stdc++.h>
using namespace std;

const bool fileIO = true;
void setIO() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
}

long long decompress(string str) {
    long long total = 0;
    while (str.length() > 0) {
        if (str.find("(") != string::npos && str.find(")") != string::npos) {
            total += str.substr(0, str.find("(")).length();
            str.erase(0, str.find("(") + 1);
            int repeatLength = stoi(str.substr(0, str.find("x")));
            str.erase(0, str.find("x") + 1);
            int repeatAmount = stoi(str.substr(0, str.find(")")));
            str.erase(0, str.find(")") + 1);
            total += repeatAmount * decompress(str.substr(0, repeatLength));
            str.erase(0, repeatLength);
        }
        else {
            total += str.length();
            break;
        }
    }
    return total;
}

int main() {

    if (fileIO) { setIO(); }

    string str;
    cin >> str;

    cout << decompress(str) << endl;

    int totalLength = 0;
    while (str.length() > 0) {
        if (str.find("(") != string::npos && str.find(")") != string::npos) {
            totalLength += str.substr(0, str.find("(")).length();
            str.erase(0, str.find("(") + 1);
            int repeatLength = stoi(str.substr(0, str.find("x")));
            str.erase(0, str.find("x") + 1);
            int repeatAmount = stoi(str.substr(0, str.find(")")));
            str.erase(0, str.find(")") + 1);
            totalLength += repeatLength * repeatAmount;
            str.erase(0, repeatLength);
        }
        else {
            totalLength += str.length();
            break;
        }
    }

    cout << totalLength;

}