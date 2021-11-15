#include <bits/stdc++.h>
using namespace std;

struct edge {
    int j;
};

int v, e;
bitset<100000> vis;
vector<int> ver;
vector<edge> adj[100000];

void bfs(int i) {
    queue<int> q;
    q.push(i);
    while (!q.empty()) {
        int j = q.front();
        q.pop();
        if (vis[j])
            continue;
        vis[j] = true, ver.push_back(j);
        for (edge ed : adj[j])
            q.push(ed.j);
    }
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
        cout << "All reachable vertices in breath first order: ";
        vis.reset(), ver.clear();
        bfs(s);
        for (int i = 1; i < ver.size(); i++)
            cout << ver[i] << (i < ver.size() - 1 ? " " : "\n");
    }

    return 0;
}
