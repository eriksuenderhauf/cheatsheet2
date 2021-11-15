#include <bits/stdc++.h>

using namespace std;

#define MAXN 1000

const int inf = 1 << 30;
int n, m, d[MAXN], p[MAXN], c[MAXN];
bitset<MAXN> inq;
vector<pair<int, int>> e[MAXN];

// get the length and the indices of the nodes of the shortest path
pair<int, vector<int>> shortestPathFasterAlgorithm(int s, int t) {
  bool nwc = false;
  for (int i = 0; i < n; i++)
    d[i] = inf, p[i] = -1, c[i] = 0;
  inq.reset();
  d[s] = 0; p[s] = -2;
  queue<int> q;
  q.push(s); inq[s] = true;
  while (!q.empty()) {
    int i = q.front();
    q.pop(); inq[i] = false;
    c[i]++;
    if (c[i] >= n) {
      nwc = true;
      break;
    }
    for (pair<int, int> ed : e[i])
      if (d[i] + ed.second < d[ed.first]) {
        d[ed.first] = d[i] + ed.second;
        p[ed.first] = i;
        if (!inq[ed.first])
          q.push(ed.first), inq[ed.first] = true;
      }
  }
  if (nwc)
    d[t] = -inf, p[t] = -1;
  vector<int> path;
  int i = t;
  if (p[t] != -1)
    while (i != -2)
      path.push_back(i), i = p[i];
  reverse(path.begin(), path.end());
  return {d[t], path};
}

int main() {
  cin >> n >> m;
  int a, b, w;
  for (int i = 0; i < m; i++) {
    cin >> a >> b >> w, a--, b--;
    e[a].push_back({b, w});
  }
  int s, t;
  cin >> s >> t, s--, t--;
  pair<int, vector<int>> r = shortestPathFasterAlgorithm(s, t);
  if (r.first == inf)
    cout << "Infinity\n";
  else if (r.first == -inf)
    cout << "Negative weight circle\n";
  else {
    cout << r.first << "\n";
    cout << r.second.size() << " ";
    for (int i = 0; i < r.second.size(); i++)
      cout << r.second[i] + 1 << (i < r.second.size() - 1 ? " " : "\n");
  }
}
