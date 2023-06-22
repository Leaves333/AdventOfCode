#include <bits\stdc++.h>
using namespace std;

const bool fileIO = true;
void setIO() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
}

int main() {

    if (fileIO) { setIO(); }

    int input[20];

    for (int i = 0; i < 20; i++) {
        cin >> input[i];
    }

    int ans = 0;
    int minContainersUsed = 20;
    for (int i = 0; i < pow(2, 20); i++) {
        int sum = 0;
        int containersUsed = 0;
        for (int j = 0; j < 20; j++) {
            if (i & 1 << j) {
                sum += input[j];
                containersUsed++;
            }
        }
        if (sum == 150) {
            ans++;
            if (containersUsed < minContainersUsed) {
                minContainersUsed = containersUsed;
            }
        }
    }

    int secondPart = 0;
    for (int i = 0; i < pow(2, 20); i++) {
        int sum = 0;
        int containersUsed = 0;
        for (int j = 0; j < 20; j++) {
            if (i & 1 << j) {
                sum += input[j];
                containersUsed++;
            }
        }
        if (sum == 150 && containersUsed == minContainersUsed) {
            secondPart++;
        }
    }

    cout << ans << endl << secondPart;

}