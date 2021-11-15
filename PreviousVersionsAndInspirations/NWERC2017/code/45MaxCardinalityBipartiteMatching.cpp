struct edge {
    int j;
};

int v, e, mbm, mat[1000], lev[1000];
bool ibg;
bitset<1000> vis;
vector<int> vl;
vector<edge> adj[1000];

bool findPath(int i) {
    for (edge ed : adj[i])
        if (!vis[ed.j]) {
            vis[ed.j] = true;
            if (mat[ed.j] == -1 || findPath(mat[ed.j])) {
                mat[i] = ed.j;
                mat[ed.j] = i;
                return true;
            }
        }
    return false;
}

void dfs(int i, int l = 1) {
    lev[i] = l;
    if (lev[i] == 1)
        vl.push_back(i);
    for (edge ed : adj[i]) {
        if (!lev[ed.j])
            dfs(ed.j, 3 - l);
        else
            ibg = ibg && lev[i] != lev[ed.j];
    }
}

void maxCardinalityBipartiteMatching() {
    mbm = 0;
    ibg = true;
    vl.clear();
    for (int i = 0; i < v; i++) {
        mat[i] = -1;
        if (!lev[i])
            dfs(i);
    }
    if (!ibg)
        return;
    for (int i : vl) {
        vis.reset();
        if (mat[i] == -1)
            mbm += findPath(i);
    }
}

int main() {
    cin >> v >> e;
    int a, b;
    for (int i = 0; i < e; i++) {
        cin >> a >> b;
        adj[a].push_back({b});
        adj[b].push_back({a});
    }

    maxCardinalityBipartiteMatching();

    if (ibg) {
        //the maximum cardinality bipartite matching
        mbm;
        for (int i : vl)
            if (mat[i] != -1)
                mat[i];
    } //else no bipartite graph
}
