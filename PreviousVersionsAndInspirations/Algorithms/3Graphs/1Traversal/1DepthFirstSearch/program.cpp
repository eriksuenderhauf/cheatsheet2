#include <bits/stdc++.h>

using namespace std;

#define MAXN 100000

int n, m;
bitset<MAXN> v;
vector<int> o, e[MAXN];

// get the indices of the nodes in depth first search order
void dfs(int i) {
  if (v[i])
    return;
  v[i] = true;
  o.push_back(i);
  for (int j : e[i])
    dfs(j);
}

int main() {
  cin >> n >> m;
  int a, b;
  for (int i = 0; i < m; i++) {
    cin >> a >> b, a--, b--;
    e[a].push_back(b);
  }
  int s;
  cin >> s, s--;
  dfs(s);
  cout << o.size() << "\n";
  for (int i = 0; i < o.size(); i++)
    cout << o[i] + 1 << (i < o.size() - 1 ? " " : "\n");
}
