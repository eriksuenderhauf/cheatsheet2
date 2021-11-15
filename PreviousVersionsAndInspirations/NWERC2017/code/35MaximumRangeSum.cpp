int main() {
    int n, a, s = 0, m = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a;
        s = max(0, s + a);
        m = max(m, s);
    }
    //the maximum range sum
    m;
}
