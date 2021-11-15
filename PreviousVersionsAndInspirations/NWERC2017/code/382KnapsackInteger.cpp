int n, k, v[1000], w[1000], a[1000], m[1001][1000], u[1001][1000];

int main() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> v[i];
    for (int i = 0; i < n; i++)
        cin >> w[i];
    for (int i = 0; i < n; i++)
        cin >> a[i];
    cin >> k;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < w[i] && j <= k; j++) {
            int c = j;
            deque<int> d;
            while (c <= k) {
                while (!d.empty() && (c - d.front()) / w[i] > a[i])
                    d.pop_front();
                while (!d.empty() && m[i][c] >= m[i][d.back()] + v[i] * (c - d.back()) / w[i])
                    d.pop_back();
                d.push_back(c);
                u[i + 1][c] = (c - d.front()) / w[i];
                m[i + 1][c] = m[i][d.front()] + v[i] * u[i + 1][c];
                c += w[i];
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
