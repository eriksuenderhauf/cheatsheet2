struct AhoCorasick  {
  #define ep emplace_back
  vector<array<int,26>> go;
  vector<int> fin, lnk;
  int cnt;
  AhoCorasick() : cnt(0) { add(); }
  AhoCorasick(const vector<string> &S) : cnt(0) {
    add();
    for (auto &s : S) {
      int cur = 0;
      for (auto c: s) {
        if (!go[cur][c-'a'])
          go[cur][c-'a'] = cnt, add(), lnk[cnt-1] = -1;
        cur = go[cur][c-'a'];
      }
      fin[cur]++;
    }
    lnk[0] = -1;
    for (queue<int> q({0}); !q.empty();) {
      int u = q.front(); q.pop();
      if (u) fin[u] += fin[lnk[u]];
      for (int i = 0; i < 26; i++) {
        int v = go[u][i];
        if (v) {
          lnk[v] = ~lnk[u] ? go[lnk[u]][i] : 0;
          q.push(v);
        }
        if (u) go[u][i] = v ? v : go[lnk[u]][i];
      }
    }
  }
  void add() {
    cnt++, go.ep(), fin.ep(), lnk.ep();
  }
  int query(const string &s) {
    int cur = 0, ans = 0;
    for (char c : s) {
      cur = go[cur][c-'a'];
      ans += fin[cur];
    }
    return ans;
  }
};