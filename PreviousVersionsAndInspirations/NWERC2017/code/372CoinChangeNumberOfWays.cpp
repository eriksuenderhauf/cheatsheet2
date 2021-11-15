int n, v[1000], w[1000];

int main() {
    cin >> n;
    w[0] = 1;
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        for (int j = v[i]; j < 1000; j++)
            w[j] += w[j - v[i]];
    }

    //the number of ways
    w[c];
}
