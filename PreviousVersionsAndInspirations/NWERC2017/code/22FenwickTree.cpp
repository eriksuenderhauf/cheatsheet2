#define LSOne(S) (S & (-S))

int n, v[1000000], f[1000000];

void change(int i, int d) {
    for (; i <= n; i += LSOne(i))
        f[i] += d;
}

int getSum(int i) {
    int sum = 0;
    for (; i; i -= LSOne(i))
        sum += f[i];
    return sum;
}

int getSum(int a, int b) {
    return getSum(b) - getSum(a - 1);
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> v[i + 1], change(i + 1, v[i + 1]);
    int x, y;
    //change value at position x
    change(x + 1, y - v[x + 1]), v[x + 1] = y;
    //get sum of the range [x, y]
    getSum(x + 1, y + 1);
}
