#include <bits/stdc++.h>
using namespace std;

struct edge {
    int j;
};

int v, e, c, cm[100000];
bitset<100000> vis;
vector<int> ccm;
vector<vector<int>> com;
vector<edge> adj[100000];

void dfs(int i) {
    if (vis[i])
        return;
    vis[i] = true, cm[i] = c, ccm.push_back(i);
    for (edge ed : adj[i])
        dfs(ed.j);
}

int main() {
    cout << "Enter the amount of vertices and edges: ";
    cin >> v >> e;
    cout << "Enter the edges a<->b: ";
    int a, b;
    for (int i = 0; i < e; i++) {
        cin >> a >> b;
        adj[a].push_back({b});
        adj[b].push_back({a});
    }

    for (int i = 0; i < v; i++)
        if (!vis[i]) {
            dfs(i);
            com.push_back(ccm);
            ccm.clear();
            c++;
        }

    cout << "The number of found components: " << c << "\n";
    cout << "All found components:\n";
    for (vector<int> cm : com)
        for (int i = 0; i < cm.size(); i++)
            cout << cm[i] << (i < cm.size() - 1 ? " " : "\n");

    return 0;
}
