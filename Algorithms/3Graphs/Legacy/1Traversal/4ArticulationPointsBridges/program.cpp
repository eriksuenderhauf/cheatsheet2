#include <bits/stdc++.h>

using namespace std;

#define MAXN 100000

int n, m, cou, num[MAXN], low[MAXN];
bitset<MAXN> v;
vector<int> art, e[MAXN];
vector<pair<int, int>> bri;

void dfs(int i, int p = -1) {
  v[i] = true; num[i] = low[i] = cou++;
  bool root = p == -1;
  int sub = 0, high = 0;
  for (int j : e[i]) {
    if (j == p) {
      p = -1;
      continue;
    }
    if (v[j])
      low[i] = min(low[i], num[j]);
    else {
      dfs(j, i);
      if (low[j] > num[i])
        bri.push_back({i, j});
      low[i] = min(low[i], low[j]);
      high = max(high, low[j]);
      sub++;
    }
  }
  if (!root && high >= num[i] || root && sub > 1)
    art.push_back(i);
}

// get the indices of the articulation points and the bridges
void articulationPointsBridges() {
  v.reset(); art.clear(); bri.clear(); cou = 0;
  for (int i = 0; i < n; i++)
    if (!v[i])
      dfs(i);
}

int main() {
  cin >> n >> m;
  int a, b;
  for (int i = 0; i < m; i++) {
    cin >> a >> b, a--, b--;
    e[a].push_back(b);
    e[b].push_back(a);
  }
  articulationPointsBridges();
  cout << art.size() << "\n";
  for (int i = 0; i < art.size(); i++)
    cout << art[i] + 1 << (i < art.size() - 1 ? " " : "\n");
  cout << bri.size() << "\n";
  for (pair<int, int> ed : bri)
    cout << ed.first + 1 << " " << ed.second + 1 << "\n";
}
