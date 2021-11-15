#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll inf = LLONG_MAX / 4;

struct min_cost_max_flow {
  struct edge {
    ll j, f, c, p, r;
  };
  int n;
  vector<int> p;
  vector<ll> d, pi;
  vector<vector<edge>> e;
  min_cost_max_flow(int n) : n(n), p(n), d(n), e(n) {}
  void addEdge(int i, int j, ll c, ll p) {
    e[i].push_back({j, 0, c, p, e[j].size() + (i == j)});
    e[j].push_back({i, 0, 0, -p, e[i].size() - 1});
  }
  void path(int s) {
    swap(d, pi);
    d.assign(n, inf);
    d[s] = 0;
    priority_queue<pair<ll, int>> pq;
    pq.push({0, s});
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
          pq.push({-(d[ed.j] - pi[ed.j]), ed.j});
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

int main() {
  int n, m, s, t, a, b, c, p;
  cin >> n >> m;
  min_cost_max_flow mcmf(n);
  for (int i = 0; i < m; i++) {
    cin >> a >> b >> c >> p, a--, b--;
    mcmf.addEdge(a, b, c, p);
  }
  cin >> s >> t, s--, t--;
  mcmf.setPi(s);
  pair<ll, ll> r = mcmf.minCostMaxFlow(s, t);
  cout << r.first << " " << r.second << "\n";
}