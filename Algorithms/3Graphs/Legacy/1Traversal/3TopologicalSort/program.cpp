#include <bits/stdc++.h>

using namespace std;

#define MAXN 100000

int n, m, d[MAXN];
vector<int> e[MAXN];

// get the indices of the nodes in topological order
vector<int> topologicalSort() {
  for (int i = 0; i < n; i++)
    d[i] = 0;
  for (int i = 0; i < n; i++)
    for (int j : e[i])
      d[j]++;
  vector<int> o;
  queue<int> q;
  for (int i = 0; i < n; i++)
    if (d[i] == 0)
      q.push(i);
  while (!q.empty()) {
    int j = q.front();
    q.pop();
    o.push_back(j);
    for (int k : e[j]) {
      d[k]--;
      if (d[k] == 0)
        q.push(k);
    }
  }
  return o;
}

int main() {
  cin >> n >> m;
  int a, b;
  for (int i = 0; i < m; i++) {
    cin >> a >> b, a--, b--;
    e[a].push_back(b);
  }
  vector<int> o = topologicalSort();
  if (o.size() < n)
    cout << "No\n";
  else {
    cout << "Yes\n";
    for (int i = 0; i < o.size(); i++)
      cout << o[i] + 1 << (i < o.size() - 1 ? " " : "\n");
  }
}
