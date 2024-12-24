#include <bits/stdc++.h>
using namespace std;

string stringify(set<string> x) {
    string ret;
    for (string s : x) {
        ret += s + ", ";
    }
    return ret;
}

set<string> largest_complete_subgraph;
void bron_kerbosch(set<string> r, set<string> p, set<string> x,
                   const map<string, set<string>> &edges) {

    if (p.size() == 0 && x.size() == 0) {
        if (r.size() > largest_complete_subgraph.size()) {
            largest_complete_subgraph = r;
        }
        return;
    }

    vector<string> remaining_vertices(p.begin(), p.end());
    for (auto v : remaining_vertices) {

        set<string> new_r;
        new_r.insert(v);
        for (auto s : r)
            new_r.insert(s);

        set<string> new_p;
        set<string> new_x;
        for (string neighbor : edges.at(v)) {
            if (p.count(neighbor))
                new_p.insert(neighbor);
            if (x.count(neighbor))
                new_x.insert(neighbor);
        }

        bron_kerbosch(new_r, new_p, new_x, edges);
        p.erase(v);
        x.insert(v);

    }
}

int main() {

    fstream fin("input.txt");
    map<string, set<string>> edges;
    while (true) {
        string s;
        fin >> s;
        if (fin.eof())
            break;
        string first = s.substr(0, 2);
        string second = s.substr(3, 2);
        edges[first].insert(second);
        edges[second].insert(first);
    }

    set<vector<string>> seen;
    for (const auto &[first, edges_first] : edges) {
        for (const auto second : edges_first) {
            if (!edges[second].count(first))
                continue;
            for (const auto third : edges[second]) {
                if (!edges[third].count(first))
                    continue;
                if (first[0] != 't' && second[0] != 't' && third[0] != 't')
                    continue;

                vector<string> connected;
                connected.push_back(first);
                connected.push_back(second);
                connected.push_back(third);
                sort(connected.begin(), connected.end());
                seen.insert(connected);
            }
        }
    }

    cout << "part 1: " << seen.size() << endl;

    // bron-kerbosch???
    set<string> r, p, x;
    for (const auto &[key, value] : edges)
        p.insert(key);
    bron_kerbosch(r, p, x, edges);

    cout << "best complete graph: " << endl;
    for (string s : largest_complete_subgraph) {
        cout << s << ",";
    }
    cout << endl;
    
}
