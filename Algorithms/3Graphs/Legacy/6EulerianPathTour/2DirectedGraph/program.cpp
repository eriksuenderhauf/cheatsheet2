#include <bits/stdc++.h>

using namespace std;

#define MAXN 100000

struct edge {
  int j;
  bool v;
};

int n, m, din[MAXN], dou[MAXN], nxt[MAXN];
bool ieg, het;
vector<edge> e[MAXN];

void addEdge(int i, int j) {
  e[i].push_back({j, false});
  dou[i]++;
  din[j]++;
}

// get the indices of the vertices of an euler path
vector<int> eulerPathTour() {
  int i = 0, ddv = 0;
  for (int j = 0; j < n; j++) {
    nxt[j] = 0;
    ddv += abs(din[j] - dou[j]);
    if (dou[j] > 0 && ddv == 0 || abs(din[j] - dou[j]) > 0 && dou[j] > din[j])
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
      ed.v = true;
      s.push(ed.j);
    } else
      s.pop(), v.push_back(i);
  }
  reverse(v.begin(), v.end());
  ieg = ddv <= 2 && v.size() == m + 1;
  het = ieg && ddv == 0;
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
