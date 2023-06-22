#include <bits\stdc++.h>
using namespace std;

const bool fileIO = true;
void setIO() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
}

const int INPUT_SIZE = 29;
vector<int> input;
int target;
long long minEntanglement = LLONG_MAX;
int minSize = INT_MAX;
int k = 0;

void subsetSum(vector<int> numbers, int target, vector<int> partial) {

    int sum = 0;
    for (int a : partial) { sum += a; }

    k++;
    k %= 10000;


    if (sum == target) {
        if (partial.size() < minSize) {
            minSize = partial.size();
            long long mult = 1;
            for (int a : partial) { mult *= a; }
            minEntanglement = mult;

        }
        else if (partial.size() == minSize) {
            long long mult = 1;
            for (int a : partial) { mult *= a; }
            if (mult < minEntanglement) {
                minEntanglement = mult;
            }
        }
    }
    if (sum >= target || partial.size() > minSize) {
        return;
    }

    for (int i = 0; i < numbers.size(); i++) {
        vector<int> remaining (numbers);
        vector<int> partialler (partial);
        remaining.erase(remaining.begin() + i);
        partialler.push_back(numbers[i]);
        subsetSum(remaining, target, partialler);
    }

}

int main() {

    if (fileIO) { setIO(); }

    int sum = 0;
    for (int i = 0; i < INPUT_SIZE; i++) {
        int x; cin >> x;
        input.push_back(x);
        sum += x;
    }
    target = sum / 4;
    reverse(input.begin(), input.end());
    vector<int> empty;
    subsetSum(input, target, empty);

    printf("part 1: %d\n%d", minEntanglement, minSize);

}