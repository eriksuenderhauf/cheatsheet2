#include <bits/stdc++.h>
#define vi vector<int>
#define pb push_back
using namespace std;
typedef long long ll;

struct dinic {
  struct edge {
    ll j, c, f;
  };

  const ll flow_inf = 1e18;
  vector<edge> e;
  vector<vector<int>> adj;
  vector<int> lvl, ptr;
  int n, m = 0;
  queue<int> q;

  dinic(int n) : n(n), adj(n), lvl(n), ptr(n) {}

  void addEdge(int i, int j, ll c) {
    e.push_back({j, c, 0});
    e.push_back({i, 0, 0});
    adj[i].push_back(m++);
    adj[j].push_back(m++);
  }

  bool bfs(int s, int t) {
    fill(lvl.begin(), lvl.end(), -1);
    lvl[s] = 0;
    q.push(s);
    while (!q.empty()) {
      int v = q.front(); q.pop();
      for (int i : adj[v])
        if (e[i].c != e[i].f && lvl[e[i].j] == -1) {
          lvl[e[i].j] = lvl[v] + 1;
          q.push(e[i].j);
        }
    }
    return lvl[t] != -1;
  }

  ll dfs(int v, int t, ll push) {
    if (push == 0 || v == t)
      return push;
    for (int& idx = ptr[v]; idx < (int)adj[v].size(); idx++) {
      int id = adj[v][idx];
      if (lvl[v] + 1 != lvl[e[id].j] || e[id].c == e[id].f)
        continue;
      ll f = dfs(e[id].j, t, min(push, e[id].c - e[id].f));
      if (f != 0) {
        e[id].f += f;
        e[id ^ 1].f -= f;
        return f;
      }
    }
    return 0;
  }

  ll maxFlow(int s, int t) {
    ll ret = 0;
    while (bfs(s, t)) {
      fill(ptr.begin(), ptr.end(), 0);
      while (ll f = dfs(s, t, flow_inf))
        ret += f;
    }
    return ret;
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(nullptr);
  int T; cin >> T;
  while (T--) {
    int n, m, k, a, b;
    cin >> n >> m >> k;
    dinic g(n*n+2);
    g.addEdge(0, 1, k);
    for (int i = 0; i < m; i++) {
      cin >> a >> b;
      for (int j = 0; j+1 < n; j++)
        g.addEdge(j * n + a, (j+1) * n + b, 1);
    }
    bool fl = true;
    int cur = 0;
    for (int i = 0; i < n; i++) {
      g.addEdge(i * n + n, n*n+1, k);
      cur += g.maxFlow(0, n*n+1);
      if (cur == k) {
        cout << i << "\n";
        fl = false;
        break;
      }
    }
    if (fl)
      cout << "-1\n";
  }
  return 0;
}