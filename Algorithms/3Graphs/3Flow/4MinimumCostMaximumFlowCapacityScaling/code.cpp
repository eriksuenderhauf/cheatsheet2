typedef long long ll;
const ll inf = LLONG_MAX / 4;

struct min_cost_max_flow {
  struct edge {
    ll j, f, c, oc, p, r;
  };
  int n;
  ll mc = 0, mp = 0;
  vector<int> p;
  vector<ll> d, pi;
  vector<vector<edge>> e;
  min_cost_max_flow(int n) : n(n), p(n), d(n), pi(n), e(n) {}
  void addEdge(int i, int j, ll c, ll p) {
    mc = max(mc, c); mp = max(mp, abs(p));
    e[i].push_back({j, 0, 0, c, p, e[j].size() + (i == j)});
    e[j].push_back({i, 0, 0, 0, -p, e[i].size() - 1});
  }
  void path(int s) {
    d.assign(n, inf);
    d[s] = 0;
    priority_queue<pair<ll, int>> pq;
    pq.push({pi[s], s});
    ll md = 0;
    while (!pq.empty()) {
      ll di = pq.top().first;
      int i = pq.top().second;
      pq.pop();
      if (-di != d[i] - pi[i])
        continue;
      md = max(md, d[i]);
      for (edge & ed : e[i]) {
        ll v = d[i] + ed.p;
        if (ed.c > ed.f && v < d[ed.j]) {
          d[ed.j] = v; p[ed.j] = ed.r;
          pq.push({-(d[ed.j] - pi[ed.j]), ed.j});
        }
      }
    }
    for (int i = 0; i < n; i++)
      if (d[i] < inf)
        pi[i] += d[i] - md;
  }
  void augment(int s, int t) {
    for (int i = t; i != s; i = e[i][p[i]].j) {
      edge & ed = e[e[i][p[i]].j][e[i][p[i]].r];
      e[i][p[i]].f -= 1;
      ed.f += 1;
    }
  }
  pair<ll, ll> minCostMaxFlow(int s, int t) {
    addEdge(t, s, 1LL << 60, - n * mp - 1);
    ll f = 0, c = 0;
    int b = 0;
    while ((1LL << b) < mc)
      b++;
    for (; b >= 0; b--) {
      c *= 2;
      for (int i = 0; i < n; i++)
        for (edge & ed : e[i])
          ed.c *= 2, ed.f *= 2;
      for (int i = 0; i < n; i++)
        for (edge & ed : e[i])
          if ((ed.oc >> b) & 1) {
            if (ed.c == ed.f) {
              path(ed.j);
              if (d[i] < inf && d[i] + ed.p < 0) {
                c += d[i] + ed.p;
                e[ed.j][ed.r].f -= 1;
                ed.f += 1;
                augment(ed.j, i);
              }
            }
            ed.c += 1;
          }
    }
    f = e[t].back().f;
    c -= f * e[t].back().p;
    return {f, c};
  }
};
