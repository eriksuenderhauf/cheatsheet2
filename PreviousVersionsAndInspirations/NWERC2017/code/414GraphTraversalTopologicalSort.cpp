struct edge {
    int j;
};

int v, e, n, deg[100000];
vector<int> ver;
vector<edge> adj[100000];

int main() {
    cin >> v >> e;
    int a, b;
    for (int i = 0; i < e; i++) {
        cin >> a >> b;
        adj[a].push_back({b});
        deg[b]++;
    }

    queue<int> q;
    for (int i = 0; i < v; i++)
        if (deg[i] == 0)
            q.push(i);
    while (!q.empty()) {
        int i = q.front();
        q.pop();
        ver.push_back(i);
        n++;
        for (edge ed : adj[i]) {
            deg[ed.j]--;
            if (deg[ed.j] == 0)
                q.push(ed.j);
        }
    }

    //a topological sorting of the graph if n < v
    for (int i = 0; i < ver.size(); i++)
        ver[i];
}
