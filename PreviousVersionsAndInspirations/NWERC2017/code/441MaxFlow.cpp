struct edge {
    int j, c, f, inv;
};

const int inf = 1 << 30;
int v, e, s, t, mfl, lev[400], nxt[400];
vector<edge> adj[400];

int sendFlow(int i = s, int f = inf) {
    if (i == t)
        return f;
    for (; nxt[i] < adj[i].size(); nxt[i]++) {
        edge & ed = adj[i][nxt[i]];
        if (lev[ed.j] == lev[i] + 1 && ed.f < ed.c) {
            int cf = min(f, ed.c - ed.f);
            int tf = sendFlow(ed.j, cf);
            if (tf > 0) {
                ed.f += tf;
                adj[ed.j][ed.inv].f -= tf;
                return tf;
            }
        }
    }
    return 0;
}

bool bfs() {
    memset(lev, -1, sizeof lev);
    lev[s] = 0;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int i = q.front();
        q.pop();
        for (edge ed : adj[i])
            if (lev[ed.j] == -1 && ed.f < ed.c)
                lev[ed.j] = lev[i] + 1, q.push(ed.j);
    }
    return lev[t] >= 0;
}

void maxFlow() {
    if (s == t) {
        mfl = inf;
        return;
    }
    mfl = 0;
    while (bfs()) {
        memset(nxt, 0, sizeof nxt);
        while (int f = sendFlow())
            mfl += f;
    }
}

int main() {
    cin >> v >> e >> s >> t;
    int a, b, c;
    for (int i = 0; i < e; i++) {
        cin >> a >> b >> c;
        adj[a].push_back({b, c, 0, adj[b].size()});
        adj[b].push_back({a, 0, 0, adj[a].size() - 1});
    }

    maxFlow();

    //the maximum flow
    mfl;
    //the flow
    for (int i = 0; i < v; i++)
        for (edge ed : adj[i])
            if (ed.f > 0)
                ed;
}
