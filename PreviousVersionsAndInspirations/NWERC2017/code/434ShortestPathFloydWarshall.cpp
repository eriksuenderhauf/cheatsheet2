int v, e, d[400][400], p[400][400];
bool nwc = false; stack<int> ver;

void floydWarshall(int i, int j) {
    if (d[i][j] < inf && !nwc)
        while (j != i)
            ver.push(j), j = p[i][j];
}

int main() {
    cin >> v >> e;
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++)
            d[i][j] = inf, p[i][j] = i;
        d[i][i] = 0;
    }
    int a, b, w;
    for (int i = 0; i < e; i++)
        cin >> a >> b >> w, d[a][b] = w;

    for (int k = 0; k < v; k++)
        for (int i = 0; i < v; i++)
            for (int j = 0; j < v; j++)
                if (d[i][k] < inf && d[k][j] < inf && d[i][k] + d[k][j] < d[i][j])
                    d[i][j] = d[i][k] + d[k][j], p[i][j] = p[k][j];
    for (int i = 0; i < v; i++)
        if (d[i][i] < 0)
            nwc = true;

    floydWarshall(s, t);
}
