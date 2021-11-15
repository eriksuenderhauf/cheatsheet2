int n, a[100000], m[17][100000];

int getMaximum(int l, int r) {
    int s = (int) log2(r - l + 1);
    return a[m[s][l]] > a[m[s][r - (1 << s) + 1]] ? m[s][l] : m[s][r - (1 << s) + 1];
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i], m[0][i] = i;
    for (int j = 1; 1 << j <= n; j++)
        for (int i = 0; i + (1 << j) <= n; i++)
            m[j][i] = a[m[j - 1][i]] > a[m[j - 1][i + (1 << (j - 1))]] ? m[j - 1][i] : m[j - 1][i + (1 << (j - 1))];
    int l, r;
    //get the maximum in the range [l, r]
    a[getMaximum(l, r)];
}
