#include <bits\stdc++.h>
using namespace std;

const bool fileIO = true;
void setIO() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
}

bool isValid(int a, int b, int c) {
    return (a + b > c) && (b + c > a) && (c + a > b);
}

int main() {

    if (fileIO) { setIO(); }

    int ans = 0;
    for (int i = 0; i < 1902 / 3; i++) {
        int a, b, c, d, e, f, g, h, k;
        cin >> a >> b >> c >> d >> e >> f >> g >> h >> k;
        if (isValid(a, d, g)) {
            ans++;
        }
        if (isValid(b, e, h)) {
            ans++;
        }
        if (isValid(c, f, k)) {
            ans++;
        }
    }
    cout << ans;

}