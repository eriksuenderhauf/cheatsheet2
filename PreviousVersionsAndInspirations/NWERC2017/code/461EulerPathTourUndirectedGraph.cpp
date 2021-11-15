struct edge {
    int j, inv;
    bool vis;
};

int v, e, deg[100000], nxt[100000];
bool ieg, het;
bitset<100000> vis;
stack<int> ver;
vector<edge> adj[100000];

int dfs(int i) {
    int r = 1;
    vis[i] = true;
    for (edge ed : adj[i])
        if (!vis[ed.j])
            r += dfs(ed.j);
    return r;
}

void eulerPathTour() {
    int i = 0, dv = 0, odv = 0;
    for (int j = 0; j < v; j++) {
        if (deg[j] > 0) {
            dv++;
            if (odv == 0)
                i = j;
        }
        if ((deg[j] % 2) == 1) {
            odv++;
            i = j;
        }
    }
    ieg = odv <= 2 && dfs(i) == dv;
    het = ieg && odv == 0;
    stack<int> s;
    s.push(i);
    while (!s.empty()) {
        i = s.top();
        for (; nxt[i] < adj[i].size() && adj[i][nxt[i]].vis; nxt[i]++);
        if (nxt[i] < adj[i].size()) {
            edge & ed = adj[i][nxt[i]];
            ed.vis = true, adj[ed.j][ed.inv].vis = true;
            s.push(ed.j);
        } else
            s.pop(), ver.push(i);
    }
}

int main() {
    cin >> v >> e;
    int a, b;
    for (int i = 0; i < e; i++) {
        cin >> a >> b;
        adj[a].push_back({b, adj[b].size(), false});
        deg[a]++;
        adj[b].push_back({a, adj[a].size() - 1, false});
        deg[b]++;
    }

    eulerPathTour();

    //is eulerian graph
    if (ieg) {
        //has an euler tour, otherwise path
        het;
        //the tour / path
        int s = ver.top();
        ver.pop();
        while (!ver.empty())
            //s -> ver.top()
            s = ver.top(), ver.pop();
    }
}
