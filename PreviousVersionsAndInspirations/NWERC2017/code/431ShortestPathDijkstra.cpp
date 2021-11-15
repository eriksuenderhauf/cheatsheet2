struct edge {
    int j, w;
};

const int inf = 1 << 30;
int v, e, d[100000], p[100000];
stack<int> ver;
vector<edge> adj[100000];

void djikstra(int i, int j) {
    for (int k = 0; k < v; k++)
        d[k] = inf, p[k] = -1;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    d[i] = 0, p[i] = i;
    pq.push({0, i});
    while (!pq.empty()) {
        pair<int, int> v = pq.top();
        pq.pop();
        int k = v.second;
        if (v.first > d[j])
            continue;
        for (edge ed : adj[k])
            if (d[k] + ed.w < d[ed.j]) {
                d[ed.j] = d[k] + ed.w;
                p[ed.j] = k;
                pq.push({d[ed.j], ed.j});
            }
    }
    if (p[j] != -1)
        while (j != i) {
            ver.push(j);
            j = p[j];
        }
}

int main() {
    cin >> v >> e;
    int a, b, w;
    for (int i = 0; i < e; i++) {
        cin >> a >> b >> w;
        adj[a].push_back({b, w});
    }

    int s, t;
    djikstra(s, t);
    //the cost of the shortest path if p[t] != -1
    d[t];
    //the shortest path
    while (!ver.empty())
        //s -> ver.top() d[ver.top()] - d[s]
        s = ver.top(), ver.pop();
}
