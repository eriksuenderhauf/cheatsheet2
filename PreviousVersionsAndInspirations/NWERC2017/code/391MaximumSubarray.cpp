int n, m, a[1000][1000], d[1000][1000];

int main() {
    cin >> n >> m;
    for (int y = 0; y < m; y++)
        for (int x = 0; x < n; x++)
            cin >> a[x][y];

    for (int x = 0; x < n; x++)
        for (int y = 0; y < m; y++)
            d[x][y] = (a[x][y] == 0 ? 0 : (y == 0 ? 1 : d[x][y - 1] + 1));

    int maxa = 0, px = 0, py = 0, w = 0, h = 0;
    for (int y = 0; y < m; y++) {
        stack<int> s;
        for (int x = 0; x < n; x++) {
            while (!s.empty() && d[s.top()][y] > d[x][y]) {
                if ((x - s.top()) * d[s.top()][y] > maxa) {
                    w = x - s.top(); h = d[s.top()][y];
                    maxa = w * h; px = x - w; py = y + 1 - h;
                }
                s.pop();
            }
            s.push(x);
        }
        while (!s.empty()) {
            if ((n - s.top()) * d[s.top()][y] > maxa) {
                w = n - s.top(); h = d[s.top()][y];
                maxa = w * h; px = n - w; py = y + 1 - h;
            }
            s.pop();
        }
    }
    //the area of the maximum subarray
    maxa;
    //the position of the maximum subarray  [px, py]
    //the size of the maximum subarray [w, h]
}
