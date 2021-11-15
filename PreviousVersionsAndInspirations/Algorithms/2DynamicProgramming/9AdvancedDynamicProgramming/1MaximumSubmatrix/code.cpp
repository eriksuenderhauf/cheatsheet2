#define MAXN 1000

int n, m, a[MAXN][MAXN], dp[MAXN + 1][MAXN];

// get the position and size of the maximum submatrix
pair<pair<int, int>, pair<int, int>> getMaximumSubmatrix() {
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      dp[i][j] = (a[i][j] == 0 ? 0 : (j == 0 ? 1 : dp[i][j - 1] + 1));

  int ma = 0, x = 0, y = 0, w = 0, h = 0;
  for (int j = 0; j < m; j++) {
    stack<int> s;
    for (int i = 0; i <= n; i++) {
      while (!s.empty() && dp[s.top()][j] > dp[i][j]) {
        if ((i - s.top()) * dp[s.top()][j] > ma) {
          w = i - s.top(); h = dp[s.top()][j];
          ma = w * h; x = i - w; y = j + 1 - h;
        }
        s.pop();
      }
      s.push(i);
    }
  }
  return {{x, y}, {w, h}};
}
