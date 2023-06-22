#include <bits\stdc++.h>
using namespace std;

const bool fileIO = true;
void setIO() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
}

struct step {
    string a;
    string b;
    string command;
    string target;
};

bool isNumber(string s) {
    return ((string)"12345567890").find(s[0]) != string::npos;
}

int main() {

    if (fileIO) { setIO(); }

    map<string, unsigned short> circuits; circuits.clear();
    vector<step> steps; steps.clear();

    for (int i = 0; i < 339; i++) {

        string str;
        getline(cin, str);
        int spaces = 0;
        for (int j = 0; j < str.length(); j++) {
            if (str[j] == ' ') { spaces++; }
        }

        string a = "", b = "", target = "", command = "";
        if (spaces == 2) {
            a = str.substr(0, str.find(" "));
            str.erase(0, str.find(">") + 2);
            target = str;
            command = "STORE";
        }
        else if (spaces == 3) {
            str.erase(0, str.find(" ") + 1);
            a = str.substr(0, str.find(" "));
            str.erase(0, str.find(">") + 2);
            target = str;
            command = "NOT";
        }
        else if (spaces == 4) {
            a = str.substr(0, str.find(" "));
            str.erase(0, str.find(" ") + 1);
            command = str.substr(0, str.find(" "));
            str.erase(0, str.find(" ") + 1);
            b = str.substr(0, str.find(" "));
            str.erase(0, str.find(">") + 2);
            target = str;
        }

        step cur;
        cur.a = a;
        cur.b = b;
        cur.command = command;
        cur.target = target;
        steps.push_back(cur);

        //printf("(%s) (%s) (%s) (%s)\n", a.c_str(), b.c_str(), target.c_str(), command.c_str());

    }

    vector<step> backupSteps (steps.begin(), steps.end());

    while (steps.size() > 0) {

        for (int i = 0; i < steps.size(); i++) {

            step cur = steps[i];
            string command = cur.command;
            string target = cur.target;
            string a = cur.a;
            string b = cur.b;

            if (a != "" && !isNumber(a) && circuits.count(a) == 0) { continue; }
            if (b != "" && !isNumber(b) && circuits.count(b) == 0) { continue; }

            if (command == "STORE") {
                if (!isNumber(a)) { circuits[target] = circuits[a]; }
                else { circuits[target] = stoi(a); }
            }
            else if (command == "NOT") {
                circuits[target] = ~circuits[a];
            }
            else if (command == "AND") {
                if (a == "1") { circuits[target] = 1 & circuits[b]; }
                else { circuits[target] = circuits[a] & circuits[b]; } 
            }
            else if (command == "OR") {
                circuits[target] = circuits[a] | circuits[b];
            }
            else if (command == "LSHIFT") {
                circuits[target] = circuits[a] << stoi(b);
            }
            else if (command == "RSHIFT") {
                circuits[target] = circuits[a] >> stoi(b);
            }

            steps.erase(steps.begin() + i);
            break;

        }
        
    }

    cout << "answer: " << circuits["a"] << endl;
    unsigned short ansA = circuits["a"];
    circuits.clear();
    circuits["b"] = ansA;

    steps = backupSteps;
    while (steps.size() > 0) {

        for (int i = 0; i < steps.size(); i++) {

            step cur = steps[i];
            string command = cur.command;
            string target = cur.target;
            string a = cur.a;
            string b = cur.b;

            if (a != "" && !isNumber(a) && circuits.count(a) == 0) { continue; }
            if (b != "" && !isNumber(b) && circuits.count(b) == 0) { continue; }

            if (command == "STORE") {
                if (!isNumber(a)) { circuits[target] = circuits[a]; }
                else { circuits[target] = stoi(a); }
                if (target == "b") { circuits[target] = ansA; }
            }
            else if (command == "NOT") {
                circuits[target] = ~circuits[a];
            }
            else if (command == "AND") {
                if (a == "1") { circuits[target] = 1 & circuits[b]; }
                else { circuits[target] = circuits[a] & circuits[b]; } 
            }
            else if (command == "OR") {
                circuits[target] = circuits[a] | circuits[b];
            }
            else if (command == "LSHIFT") {
                circuits[target] = circuits[a] << stoi(b);
            }
            else if (command == "RSHIFT") {
                circuits[target] = circuits[a] >> stoi(b);
            }

            steps.erase(steps.begin() + i);
            break;

        }
        
    }

    cout << "answerer: " << circuits["a"] << endl;

}