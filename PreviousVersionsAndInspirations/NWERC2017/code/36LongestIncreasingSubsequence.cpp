int n, k = 0, a[100000], b[100000], v[100000], l[100000];

int main() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];

    for (int i = 0; i < n; i++) {
        int p = lower_bound(v, v + k, a[i]) - v;
        v[p] = a[i]; b[p] = i; l[i] = (p > 0 ? b[p - 1] : -1);
        k = max(k, p + 1);
    }

    //the length of the longest increasing subsequence
    k;
    int c = (k > 0 ? b[k - 1] : -1);
    stack<int> s;
    while (c != -1)
        s.push(c), c = l[c];
    //the sequence of the longest increasing subsequence
    while (!s.empty())
        a[s.top()], s.pop();
}
