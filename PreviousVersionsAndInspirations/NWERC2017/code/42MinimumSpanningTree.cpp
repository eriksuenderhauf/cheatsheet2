struct edge {
    int i, j, w;
    bool operator<(edge & b) {
        return w < b.w;
    }
};

int v, e, c, p[1000000];
edge edg[100000];
vector<edge> adj[100000];

int findSet(int i) {
    return p[i] == i ? i : (p[i] = findSet(p[i]));
}

bool inSameSet(int i, int j) {
    return findSet(i) == findSet(j);
}

void unionSet(int i, int j) {
    if (!inSameSet(i, j))
        p[findSet(i)] = findSet(j);
}

int main() {
    cin >> v >> e;
    for (int i = 0; i < v; i++)
        p[i] = i;
    int a, b, w;
    for (int i = 0; i < e; i++) {
        cin >> a >> b >> w;
        edg[i] = {a, b, w};
    }

    sort(edg, edg + e);
    for (int i = 0; i < e; i++)
        if (!inSameSet(edg[i].i, edg[i].j)) {
            c += edg[i].w;
            unionSet(edg[i].i, edg[i].j);
            adj[edg[i].i].push_back({edg[i].j, edg[i].j, edg[i].w});
            adj[edg[i].j].push_back({edg[i].i, edg[i].i, edg[i].w});
        }
    //the cost of the minimum spanning tree
    c;
    //the edges of the minimum spanning tree
    for (int i = 0; i < v; i++)
        for (edge ed : adj[i])
            ed;
}
