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
