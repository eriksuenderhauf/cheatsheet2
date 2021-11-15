#define MAXN 1000

const int inf = 1 << 30;
int n, m, d[MAXN], p[MAXN];
vector<pair<int, int>> e[MAXN];

// get the length and the indices of the nodes of the shortest path
pair<int, vector<int>> bellmanFord(int s, int t) {
  bool nwc = false;
  for (int i = 0; i < n; i++)
    d[i] = inf, p[i] = -1;
  d[s] = 0; p[s] = -2;
  for (int i = 0; i < n; i++) {
    nwc = false;
    for (int j = 0; j < n; j++)
      for (pair<int, int> ed : e[j])
        if (d[j] + ed.second < d[ed.first]) {
          d[ed.first] = d[j] + ed.second;
          p[ed.first] = j;
          nwc = true;
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
