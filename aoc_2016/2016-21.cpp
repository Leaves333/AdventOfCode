#include <bits\stdc++.h>
using namespace std;

const bool fileIO = true;
void setIO() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
}

int main() {

    if (fileIO) { setIO(); }

    string cur = "abcdefgh";
    vector<vector<string>> instructions;

    for (int i = 0; i < 100; i++) {
        string str;
        getline(cin, str);

        vector<string> input; //split the input based on spaces
        while (str.find(" ") != string::npos) {
            input.push_back(str.substr(0, str.find(" ")));
            str.erase(0, str.find(" ") + 1);
        }
        input.push_back(str);
        instructions.push_back(input);

        if (input[0] == "move") {
            int a = stoi(input[2]), b = stoi(input[5]);
            string next = cur.substr(0, a) + cur.substr(a + 1);
            next = next.substr(0, b) + cur[a] + next.substr(b);
            cur = next;
        }
        else if (input[0] == "reverse") {
            int a = stoi(input[2]), b = stoi(input[4]);
            string sub = cur.substr(a, b - a + 1);
            string reverse = "";
            for (int k = sub.length() - 1; k >= 0; k--) {
                reverse += sub[k];
            }
            cur = cur.substr(0, a) + reverse + cur.substr(b + 1);
        }
        else if (input[0] == "swap" && input[1] == "position") {
            int a = stoi(input[2]), b = stoi(input[5]);
            char temp = cur[a];
            cur[a] = cur[b];
            cur[b] = temp;
        }
        else if (input[0] == "swap" && input[1] == "letter") {
            int a = cur.find(input[2]), b = cur.find(input[5]);
            char temp = cur[a];
            cur[a] = cur[b];
            cur[b] = temp;
        }
        else if (input[0] == "rotate" && input[1] == "left") {
            int shift = stoi(input[2]);
            string next = cur.substr(shift);
            next += cur.substr(0, shift);
            cur = next;
        }
        else if (input[0] == "rotate" && input[1] == "right") {
            int shift = stoi(input[2]);
            string next = cur.substr(cur.length() - shift);
            next += cur.substr(0, cur.length() - shift);
            cur = next;
        }
        else if (input[0] == "rotate" && input[1] == "based") {
            int shift = cur.find(input[6]) + 1;
            if (shift >= 5) { shift++; }
            shift %= cur.length();
            string next = cur.substr(cur.length() - shift);
            next += cur.substr(0, cur.length() - shift);
            cur = next;
        }

    }

    cout << cur << endl;

    cur = "fbgdceah";
    for (int i = instructions.size() - 1; i >= 0; i--) {

        vector<string> input = instructions[i];

        if (input[0] == "move") {
            int b = stoi(input[2]), a = stoi(input[5]); //swapped b and a
            string next = cur.substr(0, a) + cur.substr(a + 1);
            next = next.substr(0, b) + cur[a] + next.substr(b);
            cur = next;
        }
        else if (input[0] == "reverse") {
            int a = stoi(input[2]), b = stoi(input[4]);
            string sub = cur.substr(a, b - a + 1);
            string reverse = "";
            for (int k = sub.length() - 1; k >= 0; k--) {
                reverse += sub[k];
            }
            cur = cur.substr(0, a) + reverse + cur.substr(b + 1);
        }
        else if (input[0] == "swap" && input[1] == "position") {
            int a = stoi(input[2]), b = stoi(input[5]);
            char temp = cur[a];
            cur[a] = cur[b];
            cur[b] = temp;
        }
        else if (input[0] == "swap" && input[1] == "letter") {
            int a = cur.find(input[2]), b = cur.find(input[5]);
            char temp = cur[a];
            cur[a] = cur[b];
            cur[b] = temp;
        }
        else if (input[0] == "rotate" && input[1] == "left") { //swapped rotate left and rotate right code
            int shift = stoi(input[2]);
            string next = cur.substr(cur.length() - shift);
            next += cur.substr(0, cur.length() - shift);
            cur = next;
        }
        else if (input[0] == "rotate" && input[1] == "right") {
            int shift = stoi(input[2]);
            string next = cur.substr(shift);
            next += cur.substr(0, shift);
            cur = next;
        }
        else if (input[0] == "rotate" && input[1] == "based") {

            int shift = cur.find(input[6]) + 1; //FIXING NOWWW
            if (shift >= 5) { shift++; }
            shift %= cur.length();

            int shifted = 0;
            while (shifted != shift) {

                string next = cur.substr(1);
                next += cur.substr(0, 1);
                cur = next;

                shift = cur.find(input[6]) + 1; //FIXING NOWWW
                if (shift >= 5) { shift++; }
                shift %= cur.length();
                shifted++;

            }
        }

    }

    cout << cur;

}