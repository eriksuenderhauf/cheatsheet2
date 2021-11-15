#include <bits/stdc++.h>

using namespace std;

#define MAXN 100000

const int logmaxn = (int) log2(MAXN);
int n, a[MAXN], dp[logmaxn + 1][MAXN];

void init() {
  for (int i = 0; i < n; i++)
    dp[0][i] = i;
  for (int j = 1; 1 << j <= n; j++)
    for (int i = 0; i + (1 << j) <= n; i++)
      dp[j][i] = a[dp[j - 1][i]] > a[dp[j - 1][i + (1 << (j - 1))]] ? dp[j - 1][i] : dp[j - 1][i + (1 << (j - 1))];
}

// get the index of the maximum element in the range [l, r]
int getIndexOfMaximum(int l, int r) {
  int s = (int) log2(r - l + 1);
  return a[dp[s][l]] > a[dp[s][r - (1 << s) + 1]] ? dp[s][l] : dp[s][r - (1 << s) + 1];
}

// get the maximum element in the range [l, r]
int getMaximum(int l, int r) {
  return a[getIndexOfMaximum(l, r)];
}

int main() {
  cin >> n;
  for (int i = 0; i < n; i++)
    cin >> a[i];
  init();
  int l, r;
  cin >> l >> r;
  cout << getMaximum(l - 1, r - 1) << "\n";
}
