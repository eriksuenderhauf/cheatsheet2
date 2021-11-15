#define MAXN 1000
#define MAXC 1000

int n, v[MAXN], dp[MAXC + 1];

// get the minimum number of coins needed to assemble the value c
int getMinimumNumberOfCoins(int c) {
  memset(dp, -1, sizeof dp);
  dp[0] = 0;
  for (int i = 0; i < n; i++)
    for (int j = c; j >= v[i]; j--)
      if (dp[j - v[i]] != -1 && (dp[j] == -1 || dp[j - v[i]] + 1 < dp[j]))
        dp[j] = dp[j - v[i]] + 1;
  return dp[c];
}
