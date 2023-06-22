#include <bits\stdc++.h>
using namespace std;

const bool fileIO = true;
void setIO() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
}

bool board[36][25]; //true = empty, false = blocked
int dist[36][25];
priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> q;

bool valid(int x, int y) {
    return x >= 0 && x < 36 && y >= 0 && y < 25; 
}

void updateLocation(int x, int y, int value) {
    if (dist[x][y] > value) {
        dist[x][y] = value;
        q.push(make_pair(value, make_pair(x, y)));
    }
}

void dijkstra(pair<int, int> location) {

    int x = location.first, y = location.second;
    
    if (valid(x + 1, y) && board[x + 1][y]) {
        updateLocation(x + 1, y, dist[x][y] + 1);
    }
    if (valid(x - 1, y) && board[x - 1][y]) {
        updateLocation(x - 1, y, dist[x][y] + 1);
    }
    if (valid(x, y + 1) && board[x][y + 1]) {
        updateLocation(x, y + 1, dist[x][y] + 1);
    }
    if (valid(x, y - 1) && board[x][y - 1]) {
        updateLocation(x, y - 1, dist[x][y] + 1);
    }

}

int main() {

    if (fileIO) { setIO(); }

    pair<int, int> nodes[36][25]; //used, avail
    vector<pair<int, int>> nodeList;

    string str;
    cin >> str >> str >> str; //skip first line
    cin >> str >> str >> str >> str >> str; //skip header

    for (int i = 0; i < 900; i++) {
        cin >> str;
        int x = stoi(str.substr(str.find("x") + 1, str.find("-y") - str.find("x")));
        int y = stoi(str.substr(str.find("-y") + 2));

        cin >> str >> str;
        int used = stoi(str.substr(0, str.length() - 1));
        cin >> str;
        int avail = stoi(str.substr(0, str.length() - 1));
        cin >> str;

        nodes[x][y] = make_pair(used, avail);
        nodeList.push_back(make_pair(used, avail));
    }

    int ans = 0;
    for (int i = 0; i < nodeList.size(); i++) {
        auto a = nodeList[i];
        for (int j = 0; j < nodeList.size(); j++) {
            auto b = nodeList[j];
            if (i != j && a.first != 0 && a.first <= b.second) {
                ans++;
            }
        }
    }

    cout << ans << endl;

    //initialize values
    ans = 0;
    pair<int, int> start;

    //make board
    for (int i = 0; i < 36; i++) {
        for (int j = 0; j < 25; j++) {
            auto node = nodes[i][j];
            if (node.first == 0) {
                board[i][j] = true;
                start = make_pair(i, j);
            }
            else if (node.first < 100) {
                board[i][j] = true;
            }
            else {
                board[i][j] = false;
            }
        }
    }
    //board[0][24] = false; //can't move goal data

    //print board
    for (int i = 0; i < 36; i++) {
        for (int j = 0; j < 25; j++) {
            if (i == start.first && j == start.second) {
                cout << "_ ";
            }
            else if (board[i][j]) {
                cout << ". ";
            }
            else {
                cout << "# ";
            }
        }
        cout << endl;
    }
    
    //loop through positions
    for (int i = 23; i >= 0; i--) {

        //reset distance grid
        for (int k = 0; k < 36; k++) {
            for (int l = 0; l < 25; l++) {
                dist[k][l] = INT_MAX - 1;
            }
        }
        dist[start.first][start.second] = 1;

        //do the pathfinding
        q.push(make_pair(1, start));
        while (!q.empty()) {
            int size = q.size();
            pair<int, int> uwu = q.top().second;
            dijkstra(q.top().second);
            q.pop(); 
        }

        //add result to ans
        ans += dist[0][i];

        //update board
        board[0][i] = false;
        board[0][i + 1] = true;
        start = make_pair(0, i + 1);

    }

    cout << ans << endl;

}