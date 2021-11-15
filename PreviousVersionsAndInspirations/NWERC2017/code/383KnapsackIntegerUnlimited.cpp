int n, k, v[1000], w[1000], m[1001][1000], u[1001][1000];

int main() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> v[i];
    for (int i = 0; i < n; i++)
        cin >> w[i];
    cin >> k;

    for (int i = 0; i < n; i++)
        for (int j = 0; j <= k; j++) {
            m[i + 1][j] = m[i][j];
            if (j - w[i] >= 0 && m[i + 1][j - w[i]] + v[i] > m[i + 1][j]) {
                m[i + 1][j] = m[i + 1][j - w[i]] + v[i];
                u[i + 1][j] = u[i + 1][j - w[i]] + 1;
            }
        }

    int c = 0, maxm = 0;
    for (int i = 0; i <= k; i++)
        if (m[n][i] > maxm) {
            maxm = m[n][i];
            c = i;
        }

    //the maximum possible value
    maxm;
    //the values, weights and amounts of the used objects
    for (int i = n - 1; i >= 0; i--) {
        if (u[i + 1][c] > 0)
            //[v[i], w[i], u[i + 1][c]
        c -= u[i + 1][c] * w[i];
    }
}
