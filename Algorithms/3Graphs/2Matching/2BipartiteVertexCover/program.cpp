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
  int nl, nr, m, a, b;
  cin >> nl >> nr >> m;
  vector<vector<int>> e(nl);
  for (int i = 0; i < m; i++) {
    cin >> a >> b, a--, b--;
    e[a].push_back(b);
  }
  minimum_bipartite_vertex_cover mbvc(nl, nr, e);
  cout << mbvc.mbvc << "\n";
  for (int i = 0; i < nl; i++)
    if (mbvc.cl[i])
      cout << "l " << i + 1 << "\n";
  for (int i = 0; i < nr; i++)
    if (mbvc.cr[i])
      cout << "r " << i + 1 << "\n";
}
