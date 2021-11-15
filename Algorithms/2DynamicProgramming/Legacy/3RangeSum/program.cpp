#include <bits/stdc++.h>

using namespace std;

#define MAXN 100000

int n, a[MAXN], dp[MAXN];

void init() {
  for (int i = 0; i < n; i++)
    dp[i] = a[i] + (i > 0 ? dp[i - 1] : 0);
}

// get the sum of the range [l, r]
int getSum(int l, int r) {
  return dp[r] - (l > 0 ? dp[l - 1] : 0);
}

int main() {
  cin >> n;
  for (int i = 0; i < n; i++)
    cin >> a[i];
  init();
  int l, r;
  cin >> l >> r;
  cout << getSum(l - 1, r - 1) << "\n";
}
