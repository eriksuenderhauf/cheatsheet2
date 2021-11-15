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
