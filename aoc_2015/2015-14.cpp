#include <bits\stdc++.h>
using namespace std;

const bool fileIO = true;
void setIO() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
}

struct reindeer {
    int speed, duration, rest, pos, points, currentTaskDuration;
    bool resting;
};

int main() {

    if (fileIO) { setIO(); }

    int flightDuration = 2503;
    vector<int> endingDistance;
    vector<reindeer> reindeers;

    for (int i = 0; i < 9; i++) {

        int speed, duration, rest;
        string tmp;

        cin >> tmp >> tmp >> tmp >> speed >> tmp >> tmp >> duration >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp >> rest >> tmp;
        
        reindeer deer;
        deer.speed = speed;
        deer.duration = duration;
        deer.rest = rest;
        deer.pos = 0;
        deer.points = 0;
        deer.currentTaskDuration = 0;
        deer.resting = false;
        reindeers.push_back(deer);

    }

    for (int i = 0; i < flightDuration; i++) {

        int furthestDist = 0;

        for (reindeer &deer : reindeers) {

            if (deer.resting) {
                if (deer.currentTaskDuration < deer.rest) {
                    deer.currentTaskDuration++;
                }
                else {
                    deer.resting = false;
                    deer.currentTaskDuration = 1;
                    deer.pos += deer.speed;
                }
            }
            else {
                if (deer.currentTaskDuration < deer.duration) {
                    deer.currentTaskDuration++;
                    deer.pos += deer.speed;
                }
                else {
                    deer.resting = true;
                    deer.currentTaskDuration = 1;
                }
            }

            if (deer.pos > furthestDist) {
                furthestDist = deer.pos;
            }
        }

        for (reindeer &deer : reindeers) {
            if (deer.pos == furthestDist) {
                deer.points++;
            }
        }

    }

    int longestDist = 0, mostPoints = 0;
    for (reindeer deer : reindeers) {
        if (deer.pos > longestDist) {
            longestDist = deer.pos;
        }
        if (deer.points > mostPoints) {
            //cout << deer.points << endl;
            mostPoints = deer.points;
        }
    }

    printf("distance: %d\npoints: %d", longestDist, mostPoints);

}