#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct push_relabel {
  struct edge {
    ll j, f, c, r;
  };
  int n;
  vector<bool> a;
  vector<int> h, c;
  vector<ll> x;
  vector<vector<edge>> e;
  queue<int> q;
  push_relabel(int n) : n(n), a(n), h(2 * n), c(2 * n), x(n), e(n) {}
  void addEdge(int i, int j, ll c) {
    e[i].push_back({j, 0, c, e[j].size() + (i == j)});
    e[j].push_back({i, 0, 0, e[i].size() - 1});
  }
  void activate(int i) {
    if (!a[i] && x[i] > 0)
      a[i] = true, q.push(i);
  }
  void push(int i, int j) {
    ll f = min(x[i], e[i][j].c - e[i][j].f);
    if (h[i] <= h[e[i][j].j] || f == 0)
      return;
    e[i][j].f += f; x[i] -= f;
    e[e[i][j].j][e[i][j].r].f -= f; x[e[i][j].j] += f;
    activate(e[i][j].j);
  }
  void label(int i, int k) {
    c[h[i]]--; h[i] = k; c[h[i]]++;
    activate(i);
  }
  void relabel(int i) {
    int k = 2 * n - 1;
    for (edge & ed : e[i])
      if (ed.c > ed.f)
        k = min(k, h[ed.j] + 1);
    label(i, k);
  }
  void gap(int k) {
    for (int i = 0; i < n; i++)
      if (h[i] >= k)
        label(i, max(h[i], n + 1));
  }
  void push(int i) {
    for (int j = 0; j < e[i].size() && x[i] > 0; j++)
      push(i, j);
    if (x[i] > 0)
      if (c[h[i]] == 1)
        gap(h[i]);
      else
        relabel(i);
  }
  ll maxFlow(int s, int t) {
    h[s] = n; c[0] = n - 1; c[n] = 1;
    a[s] = a[t] = true;
    for (int i = 0; i < e[s].size(); i++) {
      x[s] += e[s][i].c;
      push(s, i);
    }
    while (!q.empty()) {
      int i = q.front();
      q.pop();
      a[i] = false;
      push(i);
    }
    return x[t];
  }
};

int main() {
  int n, m, s, t, a, b, c;
  cin >> n >> m;
  push_relabel pr(n);
  for (int i = 0; i < m; i++) {
    cin >> a >> b >> c, a--, b--;
    pr.addEdge(a, b, c);
  }
  cin >> s >> t, s--, t--;
  ll r = pr.maxFlow(s, t);
  cout << r << "\n";
}
