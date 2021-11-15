#include <bits/stdc++.h>

using namespace std;

#define MAXN 100000

const int logmaxn = (int) log2(2 * MAXN);
int n, nn, ind[MAXN], ver[2 * MAXN], a[2 * MAXN], dp[logmaxn + 1][2 * MAXN];
vector<int> e[MAXN];

void dfs(int i, int p = -1, int d = 0) {
  ind[i] = nn;
  ver[nn] = i;
  a[nn++] = d;
  for (int j : e[i]) {
    if (j == p)
      continue;
    dfs(j, i, d + 1);
    ver[nn] = i;
    a[nn++] = d;
  }
}

void init(int root) {
  dfs(root);
  for (int i = 0; i < nn; i++)
    dp[0][i] = i;
  for (int j = 1; 1 << j <= nn; j++)
    for (int i = 0; i + (1 << j) <= nn; i++)
      dp[j][i] = a[dp[j - 1][i]] < a[dp[j - 1][i + (1 << (j - 1))]] ? dp[j - 1][i] : dp[j - 1][i + (1 << (j - 1))];
}

int getIndexOfMimimum(int l, int r) {
  int s = (int) log2(r - l + 1);
  return a[dp[s][l]] < a[dp[s][r - (1 << s) + 1]] ? dp[s][l] : dp[s][r - (1 << s) + 1];
}

// get the index of the lowest common ancestor of a and b
int getLowestCommonAncestor(int a, int b) {
  return ver[getIndexOfMimimum(min(ind[a], ind[b]), max(ind[a], ind[b]))];
}

int main() {
  int q, root;
  cin >> n >> q >> root, root--;
  int a, b;
  for (int i = 0; i < n - 1; i++) {
    cin >> a >> b, a--, b--;
    e[a].push_back(b);
    e[b].push_back(a);
  }
  init(root);
  for (int i = 0; i < q; i++) {
    cin >> a >> b, a--, b--;
    cout << getLowestCommonAncestor(a, b) + 1 << "\n";
  }
}
