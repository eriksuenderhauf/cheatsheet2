struct knuthOpt {
  static const int N = 1005;
  int dp[N][N], opt[N][N];
  void doDp(int n, vector<vector<int>> & C) {
    for (int i = 1; i <= n; i++)
        dp[i][i] = 0, opt[i][i] = i;
    for (int i = 1; i <= n; i++)
      for (int j = 1; j + i <= n; j++) {
        int oL = opt[j][j+i-1];
        int oR = opt[j+1][j+i];
        dp[j][j+i] = 1e9;
        for (int l = oL; l <= oR; l++) {
          int v = dp[j][l-1] + dp[l+1][j+i] + C[j][j+i];
          if (v < dp[j][j+i])
            opt[j][j+i] = l, dp[j][j+i] = v;
        }
      }
  }
};