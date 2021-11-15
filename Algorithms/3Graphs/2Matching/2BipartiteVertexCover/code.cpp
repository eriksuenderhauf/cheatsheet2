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
