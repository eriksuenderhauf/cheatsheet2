#include <bits/stdc++.h>

using namespace std;

struct articulation_points_bridges {
  int n, v = 0;
  vector<int> num, low, art;
  vector<vector<int>>& e;
  vector<pair<int, int>> bri, edg;
  articulation_points_bridges(vector<vector<int>> & e) : n(e.size()), num(n, -1), low(n), e(e) {
    for (int i = 0; i < n; i++)
      if (num[i] == -1)
        dfs(i);
  }
  void dfs(int i, int p = -1) {
    num[i] = low[i] = v++;
    int s = 0;
    bool a = false;
    for (int j : e[i]) {
      if (j == p) {
        p = -2;
        continue;
      }
      if (num[j] >= 0) {
        low[i] = min(low[i], num[j]);
        if (num[j] > num[i])
          edg.push_back({j, i});
      } else {
        edg.push_back({i, j});
        dfs(j, i);
        if (low[j] > num[i])
          bri.push_back({i, j});
        a |= low[j] >= num[i];
        low[i] = min(low[i], low[j]);
        s++;
      }
    }
    if (p == -1 ? s > 1 : a)
      art.push_back(i);
  }
};

int main() {
  int n, m, a, b;
  cin >> n >> m;
  vector<vector<int>> e(n);
  for (int i = 0; i < m; i++) {
    cin >> a >> b, a--, b--;
    e[a].push_back(b);
    e[b].push_back(a);
  }
  articulation_points_bridges apb(e);
  if (apb.bri.size())
    cout << 0 << "\n";
  else
    for (pair<int, int> ed : apb.edg)
      cout << ed.first + 1 << " " << ed.second + 1 << "\n";
}
