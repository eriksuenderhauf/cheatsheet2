typedef long long ll;
const ll inf = LLONG_MAX / 4;

struct min_cost_max_flow {
  typedef __gnu_pbds::priority_queue<pair<ll,int>> prio;
  struct edge {
    ll j, f, c, p, r;
  };
  int n;
  vector<int> p;
  vector<ll> d, pi;
  vector<vector<edge>> e;
  vector<prio::point_iterator> its;
  min_cost_max_flow(int n) : n(n), p(n), d(n), e(n), its(n) {}
  void addEdge(int i, int j, ll c, ll p) {
    e[i].push_back({j, 0, c, p, e[j].size() + (i == j)});
    e[j].push_back({i, 0, 0, -p, e[i].size() - 1});
  }
  void path(int s) {
    swap(d, pi);
    d.assign(n, inf);
    d[s] = 0;
    prio pq; its.assign(n, pq.end());
    its[s] = pq.push({0, s});
    while (!pq.empty()) {
      ll di = pq.top().first;
      int i = pq.top().second;
      pq.pop();
      if (-di != d[i] - pi[i])
        continue;
      for (edge & ed : e[i]) {
        ll v = d[i] + ed.p;
        if (ed.c > ed.f && v < d[ed.j]) {
          d[ed.j] = v; p[ed.j] = ed.r;
          if (its[ed.j] == pq.end())
            its[ed.j] = pq.push({-(d[ed.j] - pi[ed.j]), ed.j});
          else
            pq.modify(its[ed.j], {-(d[ed.j] - pi[ed.j]), ed.j});
        }
      }
    }
  }
  pair<ll, ll> minCostMaxFlow(int s, int t) {
    ll f = 0, c = 0;
    while (path(s), d[t] < inf) {
      ll w = inf;
      for (int i = t; i != s; i = e[i][p[i]].j) {
        edge & ed = e[e[i][p[i]].j][e[i][p[i]].r];
        w = min(w, ed.c - ed.f);
      }
      f += w;
      c += d[t] * w;
      for (int i = t; i != s; i = e[i][p[i]].j) {
        edge & ed = e[e[i][p[i]].j][e[i][p[i]].r];
        e[i][p[i]].f -= w;
        ed.f += w;
      }
    }
    return {f, c};
  }
  // for negative costs, call this function before min cost max flow
  void setPi(int s) {
    d.assign(n, inf);
    d[s] = 0;
    bool c = true;
    for (int i = 0; i < n && c; i++) {
      c = false;
      for (int j = 0; j < n; j++)
        for (edge & ed : e[j])
          if (ed.c > ed.f && d[j] + ed.p < d[ed.j])
            d[ed.j] = d[j] + ed.p, c = true;
    }
    assert(!c);
  }
};
