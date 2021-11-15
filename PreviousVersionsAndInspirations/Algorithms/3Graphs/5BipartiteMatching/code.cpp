#define MAXN 1000

int n, m, mat[MAXN], lev[MAXN];
bool ibg;
bitset<MAXN> v;
vector<int> vl, e[MAXN];

bool findPath(int i) {
  for (int j : e[i])
    if (!v[j]) {
      v[j] = true;
      if (mat[j] == -1 || findPath(mat[j])) {
        mat[i] = j;
        mat[j] = i;
        return true;
      }
    }
  return false;
}

void dfs(int i, int l = 1) {
  lev[i] = l;
  if (l == 1)
    vl.push_back(i);
  for (int j : e[i])
    if (!lev[j])
      dfs(j, 3 - l);
    else
      ibg = ibg && lev[i] != lev[j];
}

// get the size of the matching and the indices of the matched vertices
pair<int, vector<pair<int, int>>> maxCardinalityBipartiteMatching() {
  int mbm = 0;
  ibg = true;
  vl.clear();
  for (int i = 0; i < n; i++)
    mat[i] = -1, lev[i] = 0;
  for (int i = 0; i < n; i++)
    if (!lev[i])
      dfs(i);
  if (!ibg)
    return {-1, vector<pair<int, int>>()};
  for (int i : vl) {
    v.reset();
    if (mat[i] == -1)
      mbm += findPath(i);
  }
  vector<pair<int, int>> ma;
  for (int i : vl)
    if (mat[i] != -1)
      ma.push_back({i, mat[i]});
  return {mbm, ma};
}
