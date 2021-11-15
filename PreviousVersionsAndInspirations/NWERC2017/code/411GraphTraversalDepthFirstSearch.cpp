#include <bits/stdc++.h>
using namespace std;

struct edge {
    int j;
};

int v, e;
bitset<100000> vis;
vector<int> ver;
vector<edge> adj[100000];

void dfs(int i) {
    if (vis[i])
        return;
    vis[i] = true, ver.push_back(i);
    for (edge ed : adj[i])
        dfs(ed.j);
}

int main() {
    cout << "Enter the amount of vertices and edges: ";
    cin >> v >> e;
    cout << "Enter the edges a->b: ";
    int a, b;
    for (int i = 0; i < e; i++) {
        cin >> a >> b;
        adj[a].push_back({b});
    }

    int s;
    while (cout << "Enter the start vertex: ", cin >> s, s >= 0 && s < v) {
        cout << "All reachable vertices in depth first order: ";
        vis.reset(), ver.clear();
        dfs(s);
        for (int i = 1; i < ver.size(); i++)
            cout << ver[i] << (i < ver.size() - 1 ? " " : "\n");
    }

    return 0;
}
