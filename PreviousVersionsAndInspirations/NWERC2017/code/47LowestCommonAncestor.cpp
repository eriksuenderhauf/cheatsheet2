struct edge {
    int j;
};

int v, root, n, a[200000], m[18][200000], ind[100000], ver[200000];
vector<edge> adj[100000];

int getMaximum(int l, int r) {
    int s = (int) log2(r - l + 1);
    return a[m[s][l]] < a[m[s][r - (1 << s) + 1]] ? m[s][l] : m[s][r - (1 << s) + 1];
}

void dfs(int i, int p = -1, int d = 0) {
    ind[i] = n;
    ver[n] = i;
    a[n++] = d;
    for (edge ed : adj[i]) {
        if (ed.j == p)
            continue;
        dfs(ed.j, i, d + 1);
        ver[n] = i;
        a[n++] = d;
    }
}

int main() {
    cin >> v >> root;
    int b, c;
    for (int i = 0; i < v - 1; i++) {
        cin >> b >> c;
        adj[b].push_back({c});
        adj[c].push_back({b});
    }

    dfs(root);
    for (int i = 0; i < n; i++)
        m[0][i] = i;
    for (int j = 1; 1 << j <= n; j++)
        for (int i = 0; i + (1 << j) <= n; i++)
            m[j][i] = a[m[j - 1][i]] < a[m[j - 1][i + (1 << (j - 1))]] ? m[j - 1][i] : m[j - 1][i + (1 << (j - 1))];

    //the lowest common ancestor of two vertices b and c
    ver[getMaximum(min(ind[b], ind[c]), max(ind[b], ind[c]))];
}
