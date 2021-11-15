#include <bits/stdc++.h>

using namespace std;

#define MAXN 1000
#define MAXC 1000

int n, v[MAXN], w[MAXN], dp[MAXN + 1][MAXC + 1][2];

// get the maximum value and the used objects for a knapsack of size c
pair<int, vector<int>> getMaximumValue(int c) {
  for (int i = 0; i < n; i++)
    for (int j = 0; j <= c; j++) {
      dp[i + 1][j][0] = dp[i][j][0];
      if (j - w[i] >= 0 && dp[i][j - w[i]][0] + v[i] > dp[i + 1][j][0]) {
        dp[i + 1][j][0] = dp[i][j - w[i]][0] + v[i];
        dp[i + 1][j][1] = 1;
      }
    }
  int b = dp[n][c][0];
  vector<int> r;
  for (int i = n; i > 0; i--)
    if (dp[i][c][1] > 0)
      r.push_back(i - 1), c -= dp[i][c][1] * w[i - 1];
  reverse(r.begin(), r.end());
  return {b, r};
}

int main() {
  cin >> n;
  for (int i = 0; i < n; i++)
    cin >> v[i];
  for (int i = 0; i < n; i++)
    cin >> w[i];
  int c;
  cin >> c;
  pair<int, vector<int>> r = getMaximumValue(c);
  cout << r.first << "\n";
  for (int i = 0; i < r.second.size(); i++)
    cout << r.second[i] + 1 << (i < r.second.size() - 1 ? " " : "\n");
}
