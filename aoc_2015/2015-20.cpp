#include <bits\stdc++.h>
using namespace std;

const bool fileIO = true;
void setIO() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
}

int value(int x) {
    int total = 0;
    for (int i = 1; i <= 50; i++) {
        if (x % i == 0) {
            total += x / i * 11;
        }
    }
    return total;
}

int main() {

    if (fileIO) { setIO(); }

    const int target = 29000000;
    int i = 1;
    while (value(i) < target) {
        i++;
    }

    cout << i;

}