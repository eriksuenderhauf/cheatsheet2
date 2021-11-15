#include <bits/stdc++.h>

using namespace std;

struct strongly_connected_components {
  int n, v = 0, c = 0;
  vector<bool> ins;
  vector<int> s, num, low, com, par;
  vector<vector<int>>& e;
  strongly_connected_components(vector<vector<int>> & e) : n(e.size()), ins(n), num(n, -1), low(n), com(n), par(n), e(e) {
    for (int i = 0; i < n; i++)
      if (num[i] == -1)
        dfs(i);
  }
  // use commented lines for biconnected components in undirected graphs
  // void dfs(int i) {
  void dfs(int i, int p = -1) {
    num[i] = low[i] = v++;
    par[i] = p;
    s.push_back(i); ins[i] = true;
    for (int j : e[i]) {
      if (j == p) {
        p = -1;
        continue;
      }
      if (num[j] == -1)
        // dfs(j);
        dfs(j, i);
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
  vector<pair<int, int>> edg;
  for (int i = 0; i < m; i++) {
    cin >> a >> b, a--, b--;
    e[a].push_back(b);
    e[b].push_back(a);
    edg.push_back({a, b});
  }
  strongly_connected_components scc(e);
  vector<int> sum(scc.c);
  vector<vector<int>> ebc(scc.c);
  for (int i = 0; i < n; i++) {
    sum[scc.com[i]]++;
    for (int j : e[i])
      if (scc.com[i] != scc.com[j])
        ebc[scc.com[i]].push_back(scc.com[j]);
  }
  vector<bool> u(scc.c);
  priority_queue<pair<int, int>> pq;
  for (int i = 0; i < scc.c; i++)
    pq.push({sum[i], i});
  int ms = n;
  while (!pq.empty()) {
    int i = pq.top().second;
    pq.pop();
    ms = min(ms, sum[i]);
    if (u[i])
      continue;
    u[i] = true;
    for (int j : ebc[i])
      if (!u[j]) {
        sum[j] += sum[i];
        pq.push({sum[j], j});
      }
  }
  cout << ms << "\n";
  for (auto ed : edg) {
    int i = ed.first, j = ed.second;
    if (scc.com[i] != scc.com[j] && sum[scc.com[i]] > sum[scc.com[j]] || scc.com[i] == scc.com[j] && (scc.par[j] == i || scc.par[i] != j && scc.num[i] > scc.num[j]))
      cout << i + 1 << " " << j + 1 << "\n";
    else
      cout << j + 1 << " " << i + 1 << "\n";
  }
}
