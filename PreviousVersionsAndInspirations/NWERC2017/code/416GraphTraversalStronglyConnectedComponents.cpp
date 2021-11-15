struct edge {
    int j;
};

int v, e, n, c, num[100000], low[100000], cm[100000];
bitset<100000> vis, ins;
stack<int> s; vector<vector<int>> scc;
vector<edge> adj[100000], adg[100000];

void dfs(int i) {
    vis[i] = true, num[i] = low[i] = n++;
    s.push(i), ins[i] = true;
    for (edge ed : adj[i]) {
        if (!vis[ed.j])
            dfs(ed.j);
        if (ins[ed.j])
            low[i] = min(low[i], low[ed.j]);
    }
    if (low[i] == num[i]) {
        int j;
        vector<int> csc;
        do {
            j = s.top(), s.pop(), ins[j] = false;
            cm[j] = c, csc.push_back(j);
        } while (j != i);
        scc.push_back(csc), c++;
    }
}

int main() {
    cin >> v >> e; int a, b;
    for (int i = 0; i < e; i++)
        cin >> a >> b, adj[a].push_back({b});
    for (int i = 0; i < v; i++)
        if (!vis[i])
            dfs(i);
    for (int i = 0; i < v; i++)
        for (edge ed : adj[i])
            if (cm[i] != cm[ed.j])
                adg[cm[i]].push_back({cm[ed.j]});

    //the number of found components
    c;
    //the components
    for (vector<int> cm : scc)
        for (int i = 0; i < cm.size(); i++)
            cm[i];
    //the edges of the contracted graph
    for (int i = 0; i < c; i++)
        for (edge ed : adg[i])
            ed;
}
