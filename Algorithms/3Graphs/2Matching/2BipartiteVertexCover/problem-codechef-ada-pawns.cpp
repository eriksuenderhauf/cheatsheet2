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

struct minimum_bipartite_vertex_cover {
  int nl, nr, mbvc;
  vector<bool> cl, cr;
  vector<vector<int>>& e;
  maximum_bipartite_matching mbm;
  minimum_bipartite_vertex_cover(int nl, int nr, vector<vector<int>> & e) : nl(nl), nr(nr), cl(nl, true), cr(nr, false), e(e), mbm(nl, nr, e) {
    mbvc = mbm.mbm;
    for (int i = 0; i < nl; i++)
      if (mbm.ml[i] == -1)
        findPath(i);
  }
  void findPath(int i) {
    cl[i] = false;
    for (int j : e[i])
      if (!cr[j]) {
        cr[j] = true;
        findPath(mbm.mr[j]);
      }
  }
};

int main() {
  int t;
  cin >> t;
  for (int tt = 0; tt < t; tt++) {
    int n, m = 0;
    cin >> n;
    vector<vector<char>> c(n, vector<char>(n));
    vector<vector<bool>> d(n, vector<bool>(n));
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++) {
        cin >> c[i][j];
        d[i][j] = c[i][j] == 'O' && (i == 0 || (j == 0 || c[i - 1][j - 1] == '.') && (j == n - 1 || c[i - 1][j + 1] == '.'));
      }
    for (int i = n - 1; i > 0; i--)
      for (int j = 0; j < n; j++)
        d[i][j] = d[i][j] || c[i][j] == '.' || j > 0 && d[i - 1][j - 1] || j < n - 1 && d[i - 1][j + 1], m += c[i][j] == 'O' && (j > 0 && d[i - 1][j - 1] || j < n - 1 && d[i - 1][j + 1]);
    vector<vector<int>> e(n / 2 * n);
    for (int i = 1; i < n; i++)
      for (int j = 0; j < n; j++) {
        if (d[i][j])
          continue;
        if (j > 0 && !d[i - 1][j - 1]) {
          if (i % 2)
            e[i / 2 * n + j].push_back(i / 2 * n + j - 1);
          else
            e[(i - 1) / 2 * n + j - 1].push_back(i / 2 * n + j);
        }
        if (j < n - 1 && !d[i - 1][j + 1]) {
          if (i % 2)
            e[i / 2 * n + j].push_back(i / 2 * n + j + 1);
          else
            e[(i - 1) / 2 * n + j + 1].push_back(i / 2 * n + j);
        }
      }
    minimum_bipartite_vertex_cover mbvc(n / 2 * n, (n + 1) / 2 * n, e);
    cout << m + mbvc.mbvc << "\n";
    for (int i = n - 1; i > 0; i--)
      for (int j = 0; j < n; j++) {
        if (c[i][j] != 'O' || !d[i][j] && (i % 2 && !mbvc.cl[i / 2 * n + j] || i % 2 == 0 && !mbvc.cr[i / 2 * n + j]))
          continue;
        if (j > 0 && c[i - 1][j - 1] == 'O')
          cout << i + 1 << " " << j + 1 << " L\n";
        else if (j < n - 1 && c[i - 1][j + 1] == 'O')
          cout << i + 1 << " " << j + 1 << " R\n";
      }
  }
}
