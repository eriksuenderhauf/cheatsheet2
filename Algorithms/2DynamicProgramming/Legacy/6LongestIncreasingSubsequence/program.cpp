#include <bits/stdc++.h>

using namespace std;

#define MAXN 100000

int n, a[MAXN], v[MAXN], e[MAXN], p[MAXN];

// get the length and indices of the longest increasing subsequence
pair<int, vector<int>> getLongestIncreasingSubsequence() {
  int l = 0;
  for (int i = 0; i < n; i++) {
    int j = lower_bound(v, v + l, a[i]) - v;
    v[j] = a[i]; e[j] = i; p[i] = (j > 0 ? e[j - 1] : -1);
    l = max(l, j + 1);
  }
  vector<int> r;
  int c = (l > 0 ? e[l - 1] : -1);
  while (c != -1)
    r.push_back(c), c = p[c];
  reverse(r.begin(), r.end());
  return {l, r};
}

int main() {
  cin >> n;
  for (int i = 0; i < n; i++)
    cin >> a[i];
  pair<int, vector<int>> r = getLongestIncreasingSubsequence();
  cout << r.first << "\n";
  for (int i = 0; i < r.second.size(); i++)
    cout << r.second[i] + 1 << (i < r.second.size() - 1 ? " " : "\n");
}
