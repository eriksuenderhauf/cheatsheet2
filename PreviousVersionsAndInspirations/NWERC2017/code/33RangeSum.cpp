int n, a[1000000];

int getSum(int l, int r) {
    return a[r] - (l > 0 ? a[l - 1] : 0);
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i], a[i] += (i > 0 ? a[i - 1] : 0);
    int l, r;
    //get the sum in the range [l, r]
    getSum(l, r);
}
