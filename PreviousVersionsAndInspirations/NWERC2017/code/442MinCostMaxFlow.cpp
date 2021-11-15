struct edge {
    int j, c, co, f, inv;
};

const int inf = 1 << 30;
int v, e, s, t, mfl, mco, dst[100], pre[100], flw[100];
bitset<100000> inq;
vector<edge> adj[100];

bool sendFlow() {
    for (int i = 0; i < v; i++)
        dst[i] = inf, pre[i] = -1, flw[i] = 0;
    queue<int> q;
    inq.reset();
    dst[s] = 0, flw[s] = inf;
    q.push(s);
    inq[s] = true;
    while (!q.empty()) {
        int i = q.front();
        q.pop(), inq[i] = false;
        for (edge ed : adj[i])
            if (ed.f < ed.c && dst[i] + ed.co < dst[ed.j]) {
                dst[ed.j] = dst[i] + ed.co;
                pre[ed.j] = ed.inv;
                flw[ed.j] = min(flw[i], ed.c - ed.f);
                if (!inq[ed.j])
                    inq[ed.j] = true, q.push(ed.j);
            }
    }
    if (flw[t] == 0)
        return false;
    int i = t;
    mfl += flw[t];
    while (i != s) {
        edge & ed = adj[i][pre[i]];
        ed.f -= flw[t];
        adj[ed.j][ed.inv].f += flw[t];
        mco += flw[t] * adj[ed.j][ed.inv].co;
        i = ed.j;
    }
}

void minCostMaxFlow() {
    if (s == t) {
        mfl = inf, mco = 0;
        return;
    }
    mfl = 0, mco = 0;
    while (sendFlow());
}

int main() {
    cin >> v >> e >> s >> t;
    int a, b, c, co;
    for (int i = 0; i < e; i++) {
        cin >> a >> b >> c >> co;
        adj[a].push_back({b, c, co, 0, adj[b].size()});
        adj[b].push_back({a, 0, -co, 0, adj[a].size() - 1});
    }

    minCostMaxFlow();

    //the maximum flow
    mfl;
    //the minimum costs
    mco;
    //the flow
    for (int i = 0; i < v; i++)
        for (edge ed : adj[i])
            if (ed.f > 0)
                ed;
}
