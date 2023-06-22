#include <bits\stdc++.h>
using namespace std;

const bool fileIO = true;
void setIO() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
}

int main() {

    if (fileIO) { setIO(); }

    const string digits = "1234567890";
    int ans = 0;

    for (int i = 0; i < 1091; i++) {
        string str;
        cin >> str;
        map<char, int> frequency;

        string checksum = str.substr(str.length() - 6, 5);
        int sector = -1;
        bool ok = true;

        for (int j = 0; j < str.length() && ok; j++) {
            for (int k = 0; k < digits.length(); k++) {
                if (str[j] == digits[k]) {
                    sector = stoi(str.substr(j, str.find('[') - j));
                    ok = false;
                    break;
                }
            }
            if (str[j] != '-' && ok) {
                frequency[str[j]]++;
            }
        }

        string check = "";
        for (int j = 0; j < 5; j++) {
            int maxCount = 0;
            char mostFrequent = ' ';
            for (auto &a : frequency) {
                if (a.second > maxCount) {
                    maxCount = a.second;
                    mostFrequent = a.first;
                }
            }
            check += mostFrequent;
            frequency.erase(mostFrequent);
        }
        
        if (check == checksum) {
            ans += sector;
        }

        for (int j = 0; j < str.length(); j++) {
            if (str[j] == '-') {
                str[j] = ' ';
            }
            else {
                for (int k = 0; k < sector; k++) {
                    if (str[j] == 'z') {
                        str[j] = 'a';
                    }
                    else {
                        str[j]++;
                    }
                }
            }
        }

        printf("%s : %d\n", str.c_str(), sector);
        //printf("%d : %s : %s\n", sector, checksum.c_str(), check.c_str());
        
    }

    printf("part 1: %d\n", ans);

}