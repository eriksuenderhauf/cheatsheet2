#include <bits/stdc++.h>

using namespace std;

struct maximum_bipartite_matching {
  int nl, nr, mbm = 0;
  vector<bool> v;
  vector<int> ml, mr;
  vector<vector<int>>& e;
  maximum_bipartite_matching(int nl, int nr, vector<vector<int>> & e) : nl(nl), nr(nr), ml(nl, -1), mr(nr, -1), e(e) {
    int prv = 0;
    do {
      prv = mbm;
      v.assign(nr, false);
      for (int i = 0; i < nl; i++)
        if (ml[i] == -1)
          mbm += findPath(i);
    } while (mbm > prv);
  }
  bool findPath(int i) {
    for (int j : e[i])
      if (!v[j]) {
        v[j] = true;
        if (mr[j] == -1 || findPath(mr[j])) {
          ml[i] = j; mr[j] = i;
          return true;
        }
      }
    return false;
  }
};

int main() {
  int n, m, s, b, k, h, x, y;
  cin >> n >> m;
  vector<vector<int>> d(n, vector<int>(n, n));
  for (int i = 0; i < m; i++) {
    cin >> x >> y, x--, y--;
    d[x][y] = d[y][x] = 1;
  }
  for (int i = 0; i < n; i++)
    d[i][i] = 0;
  for (int l = 0; l < n; l++)
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        d[i][j] = min(d[i][j], d[i][l] + d[l][j]);
  cin >> s >> b >> k >> h;
  vector<int> xs(s), a(s), f(s), xb(b), db(b);
  for (int i = 0; i < s; i++)
    cin >> xs[i] >> a[i] >> f[i], xs[i]--;
  for (int i = 0; i < b; i++)
    cin >> xb[i] >> db[i], xb[i]--;
  vector<vector<int>> e(s);
  for (int i = 0; i < s; i++)
    for (int j = 0; j < b; j++)
      if (d[xs[i]][xb[j]] <= min(f[i], n - 1) && a[i] >= db[j])
        e[i].push_back(j);
  maximum_bipartite_matching mbm(s, b, e);
  cout << min(s * 1LL * h, k * 1LL * mbm.mbm) << "\n";
}
