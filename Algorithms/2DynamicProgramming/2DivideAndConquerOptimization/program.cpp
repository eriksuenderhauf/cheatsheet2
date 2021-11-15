#include <bits/stdc++.h>
using namespace std;
struct divideOpt {
  static const int N = 1005;
  int dp[2][N];
  void dfs(int i, int l, int r, int oL, int oR, vector<vector<int>> & C) {
    if (r < l)
      return;
    int m = (l + r) / 2, opt = oL;
    int & v = (dp[i][m] = 1e9);
    for (int j = oL; j <= min(oR, m-1); j++)
      if (dp[i^1][j] + C[j+1][m] < v) {
        v = dp[i^1][j] + C[j+1][m];
        opt = j;
      }
    dfs(i, l, m - 1, oL, opt, C);
    dfs(i, m + 1, r, opt, oR, C);
  }
  void doDp(int n, vector<vector<int>> & C) {
    for (int i = 1; i < n; i++)
      dfs(i&1, 0, n-1, 0, n-1, C);
  }
};

int main() {
  divideOpt d;
  int n; cin >> n;
  vector<vector<int>> C(n);
  for (int i = 0; i < n; i++) {
    C[i].resize(n);
    for (int j = 0; j < n; j++) {
      cin >> C[i][j];
    }
  }
  for (int i = 0; i < n; i++)
    d.dp[0][i] = C[0][i];
  d.doDp(n, C);
  cout << d.dp[(n&1)^1][n-1] << "\n";
  return 0;
}