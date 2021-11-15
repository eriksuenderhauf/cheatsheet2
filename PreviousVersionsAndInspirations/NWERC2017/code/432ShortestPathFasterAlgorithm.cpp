struct edge {
    int j, w;
};

const int inf = 1 << 30; int v, e, d[100000], p[100000], c[100000];
bool nwc = false; bitset<100000> inq;
stack<int> ver; vector<edge> adj[100000];

void shortestPathFasterAlgorithm(int i, int j) {
    nwc = false;
    for (int k = 0; k < v; k++)
        d[k] = inf, p[k] = -1, c[k] = 0;
    queue<int> q;
    inq.reset();
    d[i] = 0, p[i] = i;
    q.push(i);
    inq[i] = true;
    while (!q.empty()) {
        int k = q.front();
        q.pop(), inq[k] = false;
        c[k]++;
        if (c[k] >= v) {
            nwc = true;
            break;
        }
        for (edge ed : adj[k])
            if (d[k] + ed.w < d[ed.j]) {
                d[ed.j] = d[k] + ed.w;
                p[ed.j] = k;
                if (!inq[ed.j])
                    inq[ed.j] = true, q.push(ed.j);
            }
    }
    if (p[j] != -1 && !nwc)
        while (j != i)
            ver.push(j), j = p[j];
}

int main() {
    cin >> v >> e; int a, b, w;
    for (int i = 0; i < e; i++)
        cin >> a >> b >> w, adj[a].push_back({b, w});

    int s, t;
    shortestPathFasterAlgorithm(s, t);
    //the graph has a negative weight circle
    nwc;
    //the shortest path
    while (!ver.empty())
        //s -> ver.top() d[ver.top()] - d[s]
        s = ver.top(), ver.pop();
}
