typedef long long ll;
struct dinic {
  struct edge {
    ll j, c, f;
  };
  vector<edge> e;
  vector<vector<int>> adj;
  vector<int> lvl, ptr;
  int n, m = 0;
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
    for (queue<int> q = {s}; !q.empty();) {
      int v = q.front(); q.pop();
      for (int i : adj[v])
        if (e[i].c > e[i].f && lvl[e[i].j] < 0) {
          lvl[e[i].j] = lvl[v] + 1;
          q.push(e[i].j);
        }
    }
    return lvl[t] != -1;
  }
  ll dfs(int v, int t, ll push) {
    if (push == 0 || v == t)
      return push;
    for (; ptr[v] < (int)adj[v].size(); ptr[v]++) {
      int id = adj[v][ptr[v]];
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
      while (ll f = dfs(s, t, 1e18))
        ret += f;
    }
    return ret;
  }
};