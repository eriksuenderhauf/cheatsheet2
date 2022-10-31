#include <bits/stdc++.h>
using namespace std;

// O(MX_VAL*N) time and O(MX_VAL) space
int balancing01(vector<int> a, int sum) {
  int n = (int)a.size();
  sort(a.rbegin(), a.rend());
  int cur = 0, s = -1, off = sum - a[0] + 1;
  while (cur < sum && s + 1 < n)
    cur += a[++s];
  if (cur == sum || s + 1 == n && cur < sum)
    return cur;
  cur -= a[s];
  vector<int> dp(2 * a[0], 0);
  for (int i = 0; i < a[0]; i++) // remove
    dp[i] = -1;
  dp[cur - off] = s;
  for (int b = s; b < n; b++) {
    vector<int> ndp = dp;
    for (int i = 0; i < a[0]; i++) //add
      ndp[i+a[b]] = max(ndp[i+a[b]], dp[i]);
    for (int i = 2*a[0]-1; i >= a[0]; i--)
      for (int j=max(0,dp[i]); j<ndp[i]; j++)
        ndp[i - a[j]] = max(ndp[i - a[j]], j);
    dp.swap(ndp);
  }
  for (int i = a[0] - 1; i >= 0; i--)
    if (dp[i] >= 0)
      return i + off;
  return cur;
}

int main() {
  vector<int> a = {1, 4, 6, 2, 5};
  cout << balancing01(a, 200) << endl;
}