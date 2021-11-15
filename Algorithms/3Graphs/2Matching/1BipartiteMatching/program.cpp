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
  int nl, nr, m, a, b;
  cin >> nl >> nr >> m;
  vector<vector<int>> e(nl);
  for (int i = 0; i < m; i++) {
    cin >> a >> b, a--, b--;
    e[a].push_back(b);
  }
  maximum_bipartite_matching mbm(nl, nr, e);
  cout << mbm.mbm << "\n";
  for (int i = 0; i < nl; i++)
    if (mbm.ml[i] != -1)
      cout << i + 1 << " " << mbm.ml[i] + 1 << "\n";
}
