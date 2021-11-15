#include <bits/stdc++.h>

using namespace std;

#define MAXN 1000

int n, m, mat[MAXN], lev[MAXN];
bool ibg;
bitset<MAXN> v;
vector<int> vl, e[MAXN];

bool findPath(int i) {
    for (int j : e[i])
        if (!v[j]) {
            v[j] = true;
            if (mat[j] == -1 || findPath(mat[j])) {
                mat[i] = j;
                mat[j] = i;
                return true;
            }
        }
    return false;
}

void dfs(int i, int l = 1) {
    lev[i] = l;
    if (l == 1)
        vl.push_back(i);
    for (int j : e[i])
        if (!lev[j])
            dfs(j, 3 - l);
        else
            ibg = ibg && lev[i] != lev[j];
}

// get the size of the matching and the indices of the matched vertices
pair<int, vector<pair<int, int>>> maxCardinalityBipartiteMatching() {
    int mbm = 0, prev = 0;
    ibg = true;
    vl.clear();
    for (int i = 0; i < n; i++)
        mat[i] = -1, lev[i] = 0;
    for (int i = 0; i < n; i++)
        if (!lev[i])
            dfs(i);
    if (!ibg)
        return {-1, vector<pair<int, int>>()};
    do {
        prev = mbm;
        v.reset();
        for (int i : vl)
            if (mat[i] == -1)
                mbm += findPath(i);
    } while (mbm > prev);
    vector<pair<int, int>> ma;
    for (int i : vl)
        if (mat[i] != -1)
            ma.push_back({i, mat[i]});
    return {mbm, ma};
}

int main() {
    cin >> n >> m;
    int a, b;
    for (int i = 0; i < m; i++) {
        cin >> a >> b, a--, b--;
        e[a].push_back(b);
        e[b].push_back(a);
    }
    pair<int, vector<pair<int, int>>> ma = maxCardinalityBipartiteMatching();
    if (ma.first == -1)
        cout << "No bipartite graph\n";
    else {
        cout << ma.first << "\n";
        for (pair<int, int> ed : ma.second)
            cout << ed.first + 1 << " " << ed.second + 1 << "\n";
    }
}
