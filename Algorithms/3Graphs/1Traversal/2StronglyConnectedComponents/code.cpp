struct strongly_connected_components {
  int n, v = 0, c = 0;
  vector<bool> ins;
  vector<int> s, num, low, com;
  vector<vector<int>>& e;
  strongly_connected_components(vector<vector<int>> & e) : n(e.size()), ins(n), num(n, -1), low(n), com(n), e(e) {
    for (int i = 0; i < n; i++)
      if (num[i] == -1)
        dfs(i);
  }
  // use commented lines for biconnected components in undirected graphs
  void dfs(int i) {
  // void dfs(int i, int p = -1) {
    num[i] = low[i] = v++;
    s.push_back(i); ins[i] = true;
    for (int j : e[i]) {
      // if (j == p) {
      //   p = -1;
      //   continue;
      // }
      if (num[j] == -1)
        dfs(j);
        // dfs(j, i);
      if (ins[j])
        low[i] = min(low[i], low[j]);
    }
    if (low[i] == num[i]) {
      int j;
      do {
        j = s.back(); s.pop_back(); ins[j] = false;
        com[j] = c;
      } while (j != i);
      c++;
    }
  }
};
