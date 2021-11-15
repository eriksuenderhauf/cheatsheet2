#include <bits/stdc++.h>

using namespace std;

#define MAXN 1000

const int inf = 1 << 30;
int n, m, d[MAXN][MAXN], p[MAXN][MAXN];
vector<pair<int, int>> e[MAXN];

// get the length and the indices of the nodes of the shortest path
pair<int, vector<int>> floydWarshall(int s, int t) {
  bool nwc = false;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++)
      d[i][j] = inf, p[i][j] = i;
    d[i][i] = 0, p[i][i] = -2;
    for (pair<int, int> ed : e[i])
      d[i][ed.first] = min(d[i][ed.first], ed.second);
  }
  for (int k = 0; k < n; k++)
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        if (d[i][k] < inf && d[k][j] < inf && d[i][k] + d[k][j] < d[i][j])
          d[i][j] = d[i][k] + d[k][j], p[i][j] = p[k][j];
  for (int i = 0; i < n; i++)
    if (d[i][i] < 0)
      nwc = true;
  if (nwc)
    d[s][t] = -inf, p[s][t] = -1;
  vector<int> path;
  int i = t;
  if (p[s][t] != -1)
    while (i != -2)
      path.push_back(i), i = p[s][i];
  reverse(path.begin(), path.end());
  return {d[s][t], path};
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
  pair<int, vector<int>> r = floydWarshall(s, t);
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
