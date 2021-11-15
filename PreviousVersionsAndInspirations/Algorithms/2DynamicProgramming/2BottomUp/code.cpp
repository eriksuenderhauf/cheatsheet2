#define MAXN 100000

const int mod = 1000000009;
int dp[MAXN + 1];

// calculate the n-th fibonacci number
int fib(int n) {
  dp[0] = 0;
  dp[1] = 1;
  for (int i = 2; i <= n; i++)
    dp[i] = (dp[i - 1] + dp[i - 2]) % mod;
  return dp[n];
}
