#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e10 + 7;
int idx[105], sz[105];
vector<int> a[105];

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
	int n, q, s; scanf("%d %d %d", &n, &q, &s);
	dinic g((2 * q + 1) * n + 2);
	for (int i = 1; i <= s; i++)
		scanf("%d", idx+i);
	for (int i = 1; i <= q; i++)
		scanf("%d", sz+i);
	ll sm = 0;
	for (int i = 1; i <= n; i++) {
		int d; scanf("%d", &d);
		vector<int> cur(q+1);
		for (int j = 1; j <= s; j++) {
			int x; scanf("%d", &x);
			cur[idx[j]] += x;
			sm += x;
		}
		for (int j = 1; j <= q; j++) {
			g.addEdge(0, (i-1)*(2*q+1)+j, cur[j]);
			g.addEdge((i-1)*(2*q+1)+j, (i-1)*(2*q+1)+j+q, sz[j]);
			g.addEdge((i-1)*(2*q+1)+j+q, i*(2*q+1), INF);
			if (i != n)
				g.addEdge((i-1)*(2*q+1)+j+q, i*(2*q+1)+j, INF);
		}
		g.addEdge(i*(2*q+1), n*(2*q+1)+1, d);
	}
	if (g.maxFlow(0,n*(2*q+1)+1) == sm)
		printf("possible\n");
	else
		printf("impossible\n");
	return 0;
}
