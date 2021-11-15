int n, maxc = 0, v[1000], m[1000], l[1000];

int mnw(int c) {
    while (maxc < c) {
        m[++maxc] = -1;
        for (int i = 0; i < n; i++)
            if (maxc - v[i] >= 0 && m[maxc - v[i]] != -1 && (m[maxc] == -1 || m[maxc - v[i]] + 1 < m[maxc])) {
                m[maxc] = m[maxc - v[i]] + 1;
                l[maxc] = i;
            }
    }
    return m[c];
}

int main() {
    m[0] = 0;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> v[i];

    //the minimum number of coins needed if mnw(c) != -1
    mnw(c);
    //the values of the used coins
    while (c > 0)
        v[l[c]], c -= v[l[c]];
}
