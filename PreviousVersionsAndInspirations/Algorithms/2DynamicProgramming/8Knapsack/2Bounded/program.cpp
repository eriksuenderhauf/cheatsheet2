#include <bits/stdc++.h>

using namespace std;

#define MAXN 1000
#define MAXC 1000

int n, v[MAXN], w[MAXN], a[MAXN], dp[MAXN + 1][MAXC + 1][2];

// get the maximum value and the used objects for a knapsack of size c
pair<int, vector<pair<int, int>>> getMaximumValue(int c) {
  for (int i = 0; i < n; i++)
    for (int j = 0; j < w[i] && j <= c; j++) {
      int k = j;
      deque<int> d;
      while (k <= c) {
        while (!d.empty() && (k - d.front()) / w[i] > a[i])
          d.pop_front();
        while (!d.empty() && dp[i][k][0] >= dp[i][d.back()][0] + v[i] * (k - d.back()) / w[i])
          d.pop_back();
        d.push_back(k);
        dp[i + 1][k][1] = (k - d.front()) / w[i];
        dp[i + 1][k][0] = dp[i][d.front()][0] + v[i] * dp[i + 1][k][1];
        k += w[i];
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

int main() {
  cin >> n;
  for (int i = 0; i < n; i++)
    cin >> v[i];
  for (int i = 0; i < n; i++)
    cin >> w[i];
  for (int i = 0; i < n; i++)
    cin >> a[i];
  int c;
  cin >> c;
  pair<int, vector<pair<int, int>>> r = getMaximumValue(c);
  cout << r.first << "\n";
  for (int i = 0; i < r.second.size(); i++)
    cout << r.second[i].first + 1 << " " << r.second[i].second << (i < r.second.size() - 1 ? " " : "\n");
}
