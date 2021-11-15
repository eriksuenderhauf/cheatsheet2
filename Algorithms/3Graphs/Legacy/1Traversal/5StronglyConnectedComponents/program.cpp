#include <bits/stdc++.h>

using namespace std;

#define MAXN 100000

int n, m, cou, nscc, num[MAXN], low[MAXN], com[MAXN];
bitset<MAXN> v, ins;
stack<int> s;
vector<vector<int>> scc;
vector<int> e[MAXN], escc[MAXN];

void dfs(int i) {
  v[i] = true; num[i] = low[i] = cou++;
  s.push(i); ins[i] = true;
  for (int j : e[i]) {
    if (!v[j])
      dfs(j);
    if (ins[j])
      low[i] = min(low[i], low[j]);
  }
  if (low[i] == num[i]) {
    int j;
    vector<int> cscc;
    do {
      j = s.top(); s.pop(); ins[j] = false;
      com[j] = nscc; cscc.push_back(j);
    } while (j != i);
    scc.push_back(cscc); nscc++;
  }
}

// get the strongly connected components and their connections
void stronglyConnectedComponents() {
  v.reset(); scc.clear(); cou = 0; nscc = 0;
  for (int i = 0; i < n; i++) {
    escc[i].clear();
    if (!v[i])
      dfs(i);
  }
  for (int i = 0; i < n; i++)
    for (int j : e[i])
      if (com[i] != com[j])
        escc[com[i]].push_back(com[j]);
}

int main() {
  cin >> n >> m;
  int a, b;
  for (int i = 0; i < m; i++) {
    cin >> a >> b, a--, b--;
    e[a].push_back(b);
  }
  stronglyConnectedComponents();
  cout << nscc << "\n";
  for (int i = 0; i < scc.size(); i++) {
    cout << scc[i].size() << " ";
    for (int j = 0; j < scc[i].size(); j++)
      cout << scc[i][j] + 1 << (j < scc[i].size() - 1 ? " " : "\n");
    cout << escc[i].size() << (escc[i].size() > 0 ? " " : "\n");
    for (int j = 0; j < escc[i].size(); j++)
      cout << escc[i][j] + 1 << (j < escc[i].size() - 1 ? " " : "\n");
  }
}
