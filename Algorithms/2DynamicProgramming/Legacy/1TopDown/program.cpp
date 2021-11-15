#include <bits/stdc++.h>

using namespace std;

#define MAXN 100000

const int mod = 1000000009;
int n, dp[MAXN + 1];

void init() {
  memset(dp, -1, sizeof dp);
}

// calculate the n-th fibonacci number
int fib(int n) {
  if (n < 2)
    return n == 1;
  if (dp[n] == -1)
    dp[n] = (fib(n - 1) + fib(n - 2)) % mod;
  return dp[n];
}

int main() {
  init();
  cin >> n;
  cout << fib(n) << "\n";
}
