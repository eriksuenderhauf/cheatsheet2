#include <bits/stdc++.h>

using namespace std;

#define MAXN 1000
#define MAXC 1000

const int mod = 1000000009;
int n, v[MAXN], dp[MAXC + 1];

// get the number of ways to assemble the value c
int getNumberOfWays(int c) {
  dp[0] = 1;
  for (int i = 0; i < n; i++)
    for (int j = c; j >= v[i]; j--)
        dp[j] = (dp[j] + dp[j - v[i]]) % mod;
  return dp[c];
}

int main() {
  cin >> n;
  for (int i = 0; i < n; i++)
    cin >> v[i];
  int c;
  cin >> c;
  cout << getNumberOfWays(c) << "\n";
}
