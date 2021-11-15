#include <bits/stdc++.h>

using namespace std;

struct strongly_connected_components {
  int n, v = 0, c = 0;
  vector<bool> ins;
  vector<int> s, num, low, com;
  vector<vector<int>>& e;
  strongly_connected_components(vector<vector<int>> & e) : n(e.size()), ins(n), num(n, -1), low(n), com(n), e(e) {
    for (int i = 0; i < n; i++)
      if (num[i] == -1)
        dfs(i);
  }
  // use commented lines for biconnected components in undirected graphs
  void dfs(int i) {
  // void dfs(int i, int p = -1) {
    num[i] = low[i] = v++;
    s.push_back(i); ins[i] = true;
    for (int j : e[i]) {
      // if (j == p) {
      //   p = -1;
      //   continue;
      // }
      if (num[j] == -1)
        dfs(j);
        // dfs(j, i);
      if (ins[j])
        low[i] = min(low[i], low[j]);
    }
    if (low[i] == num[i]) {
      int j;
      do {
        j = s.back(); s.pop_back(); ins[j] = false;
        com[j] = c;
      } while (j != i);
      c++;
    }
  }
};

int main() {
  int n, m, a, b;
  cin >> n >> m;
  vector<vector<int>> e(n);
  for (int i = 0; i < m; i++) {
    cin >> a >> b, a--, b--;
    e[a].push_back(b);
  }
  strongly_connected_components scc(e);
  cout << scc.c << "\n";
  for (int i = 0; i < n; i++)
    cout << scc.com[i] + 1 << (i < n - 1 ? " " : "\n");
}
