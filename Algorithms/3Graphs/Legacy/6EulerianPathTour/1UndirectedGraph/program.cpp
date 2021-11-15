#include <bits/stdc++.h>

using namespace std;

#define MAXN 100000

struct edge {
  int j, inv;
  bool v;
};

int n, m, d[MAXN], nxt[MAXN];
bool ieg, het;
vector<edge> e[MAXN];

void addEdge(int i, int j) {
  e[i].push_back({j, e[j].size(), false});
  d[i]++;
  e[j].push_back({i, e[i].size() - 1, false});
  d[j]++;
}

// get the indices of the vertices of an euler path
vector<int> eulerPathTour() {
  int i = 0, odv = 0;
  for (int j = 0; j < n; j++) {
    nxt[j] = 0;
    odv += d[j] % 2;
    if (d[j] > 0 && odv == 0 || d[j] % 2 == 1)
      i = j;
  }
  stack<int> s;
  vector<int> v;
  s.push(i);
  while (!s.empty()) {
    i = s.top();
    for (; nxt[i] < e[i].size() && e[i][nxt[i]].v; nxt[i]++);
    if (nxt[i] < e[i].size()) {
      edge & ed = e[i][nxt[i]];
      ed.v = true; e[ed.j][ed.inv].v = true;
      s.push(ed.j);
    } else
      s.pop(), v.push_back(i);
  }
  reverse(v.begin(), v.end());
  ieg = odv <= 2 && v.size() == m + 1;
  het = ieg && odv == 0;
  if (!ieg)
    v.clear();
  return v;
}

int main() {
  cin >> n >> m;
  int a, b;
  for (int i = 0; i < m; i++) {
    cin >> a >> b, a--, b--;
    addEdge(a, b);
  }
  vector<int> v = eulerPathTour();
  if (!ieg)
    cout << "No Euler Path\n";
  else {
    if (het)
      cout << "An Euler tour\n";
    else
      cout << "An Euler path\n";
    cout << v.size() << "\n";
    for (int i = 0; i < v.size(); i++)
      cout << v[i] + 1 << (i < v.size() - 1 ? " " : "\n");
  }
}
