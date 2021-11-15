#define MAXN 1000
#define MAXC 1000

int n, v[MAXN], w[MAXN], dp[MAXN + 1][MAXC + 1][2];

// get the maximum value and the used objects for a knapsack of size c
pair<int, vector<pair<int, int>>> getMaximumValue(int c) {
  for (int i = 0; i < n; i++)
    for (int j = 0; j <= c; j++) {
      dp[i + 1][j][0] = dp[i][j][0];
      if (j - w[i] >= 0 && dp[i + 1][j - w[i]][0] + v[i] > dp[i + 1][j][0]) {
        dp[i + 1][j][0] = dp[i + 1][j - w[i]][0] + v[i];
        dp[i + 1][j][1] = dp[i + 1][j - w[i]][1] + 1;
      }
    }
  int b = dp[n][c][0];
  vector<pair<int, int>> r;
  for (int i = n; i > 0; i--)
    if (dp[i][c][1] > 0)
      r.push_back({i - 1, dp[i][c][1]}), c -= dp[i][c][1] * w[i - 1];
  reverse(r.begin(), r.end());
  return {b, r};
}
