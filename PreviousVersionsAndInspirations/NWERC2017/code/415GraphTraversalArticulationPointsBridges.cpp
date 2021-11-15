struct edge {
    int j, inv;
    bool br;
};

int v, e, n, num[100000], low[100000], ar[100000];
bitset<100000> vis;
vector<int> art; vector<pair<int, int>> bri;
vector<edge> adj[100000];

void dfs(int i, int p = -1) {
    vis[i] = true, num[i] = low[i] = n++;
    bool root = p == -1;
    int sub = 0, hgh = 0;
    for (edge & ed : adj[i]) {
        if (ed.j == p) {
            p = -1;
            continue;
        }
        if (vis[ed.j])
            low[i] = min(low[i], num[ed.j]);
        else {
            dfs(ed.j, i);
            if (low[ed.j] > num[i])
                ed.br = true, adj[ed.j][ed.inv].br = true, bri.push_back({i, ed.j});
            low[i] = min(low[i], low[ed.j]);
            hgh = max(hgh, low[ed.j]);
            sub++;
        }
    }
    if (!root && hgh >= num[i] || root && sub > 1)
        ar[i] = true, art.push_back(i);
}

int main() {
    cin >> v >> e; int a, b;
    for (int i = 0; i < e; i++) {
        cin >> a >> b;
        adj[a].push_back({b, adj[b].size(), false});
        adj[b].push_back({a, adj[a].size() - 1, false});
    }

    for (int i = 0; i < v; i++)
        if (!vis[i])
            dfs(i);

    //the articulation points
    for (int i = 0; i < art.size(); i++)
        art[i];
    //the bridges
    for (pair<int, int> ed : bri)
        ed;
}
