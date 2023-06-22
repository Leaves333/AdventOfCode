#include <bits\stdc++.h>
using namespace std;

const bool fileIO = true;
void setIO() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
}

const int INPUT_SIZE = 4;
vector<vector<int>> ingredients;
int maxScore = 0;
int calorieScore = 0;

void uwu(int k, vector<int> choices) {

    if (k < INPUT_SIZE) {

        int sum = 0;
        for (int n : choices) sum += n;

        if (k == INPUT_SIZE - 1) {
            choices.push_back(100 - sum);
            uwu(k + 1, choices);
            choices.pop_back();
        }
        else {
            for (int j = 0; j <= 100 - sum; j++) {
                choices.push_back(j);
                uwu(k + 1, choices);
                choices.pop_back();
            } 
        }

        return;

    }

    int qualities[5];
    memset(qualities, 0, sizeof(qualities));

    for (int i = 0; i < choices.size(); i++) {
        //cout << choices[i] << " ";
        for (int j = 0; j < 5; j++) {
            qualities[j] += choices[i] * ingredients[i][j];
        }
    }
    //cout << endl;

    for (int &n : qualities) {
        if (n < 0) { n = 0; }
    }

    int score = 1;
    for (int i = 0; i < 4; i++) {
        score *= qualities[i];
        //cout << qualities[i] << " "; 
    }
    //cout << endl;

    maxScore = max(score, maxScore);
    if (qualities[4] == 500) {
        calorieScore = max(score, calorieScore);
    }

}

int main() {

    if (fileIO) { setIO(); }

    ingredients.clear();

    for (int i = 0; i < INPUT_SIZE; i++) {

        vector<int> qualities;

        string str; cin >> str;
        for (int i = 0; i < 4; i++) {
            cin >> str >> str;
            str.substr(0, str.length() - 1);
            qualities.push_back(stoi(str)); 
        }
        cin >> str >> str; //last one doesn't have comma so its processed seperately
        qualities.push_back(stoi(str)); 

        ingredients.push_back(qualities);
        
    }

    vector<int> owo;
    owo.clear();

    uwu(0, owo);
    printf("part 1: %d\npart 2: %d", maxScore, calorieScore);

}