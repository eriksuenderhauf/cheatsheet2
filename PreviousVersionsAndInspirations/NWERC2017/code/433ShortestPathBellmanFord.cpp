const int inf = 1 << 30;
int v, e, d[100000], p[100000];
bool nwc = false;
stack<int> ver;
vector<edge> adj[100000];

void bellmanFord(int i, int j) {
    for (int k = 0; k < v; k++)
        d[k] = inf, p[k] = -1;
    d[i] = 0, p[i] = i;
    for (int k = 0; k < v; k++) {
        nwc = false;
        for (int l = 0; l < v; l++)
            for (edge ed : adj[l])
                if (d[l] < inf && d[l] + ed.w < d[ed.j])
                    d[ed.j] = d[l] + ed.w, p[ed.j] = l, nwc = true;
    }

    if (p[j] != -1 && !nwc)
        while (j != i) {
            ver.push(j);
            j = p[j];
        }
}
