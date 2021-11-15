#define MAXN 100000

const int inf = 1 << 30;
int n, m, d[MAXN], p[MAXN];
vector<pair<int, int>> e[MAXN];

// get the length and the indices of the nodes of the shortest path
pair<int, vector<int>> djikstra(int s, int t) {
  for (int i = 0; i < n; i++)
    d[i] = inf, p[i] = -1;
  d[s] = 0; p[s] = -2;
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
  pq.push({0, s});
  while (!pq.empty()) {
    pair<int, int> v = pq.top();
    pq.pop();
    int i = v.second;
    if (v.first > d[i])
      continue;
    for (pair<int, int> ed : e[i])
      if (d[i] + ed.second < d[ed.first]) {
        d[ed.first] = d[i] + ed.second;
        p[ed.first] = i;
        pq.push({d[ed.first], ed.first});
      }
  }
  vector<int> path;
  int i = t;
  if (p[t] != -1)
    while (i != -2)
      path.push_back(i), i = p[i];
  reverse(path.begin(), path.end());
  return {d[t], path};
}
