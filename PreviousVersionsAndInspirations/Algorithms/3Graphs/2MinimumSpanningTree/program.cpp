#include <bits/stdc++.h>

using namespace std;

#define MAXN 100000
#define MAXM 200000

struct edge {
  int i, j, w;
  bool operator<(edge & b) {
    return w < b.w;
  }
};

int n, m, p[MAXN];
edge ed[MAXM];
vector<int> e[MAXN];

int findSet(int i) {
  return p[i] == i ? i : (p[i] = findSet(p[i]));
}

bool inSameSet(int i, int j) {
  return findSet(i) == findSet(j);
}

void unionSet(int i, int j) {
  if (!inSameSet(i, j))
    p[findSet(i)] = findSet(j);
}

// get the costs and edges of the minimum spanning tree
int minimumSpanningTree() {
  int c = 0;
  sort(ed, ed + m);
  for (int i = 0; i < n; i++)
    p[i] = i;
  for (int i = 0; i < m; i++)
    if (!inSameSet(ed[i].i, ed[i].j)) {
      c += ed[i].w;
      unionSet(ed[i].i, ed[i].j);
      e[ed[i].i].push_back(ed[i].j);
      e[ed[i].j].push_back(ed[i].i);
    }
  return c;
}

int main() {
  cin >> n >> m;
  int a, b, w;
  for (int i = 0; i < m; i++) {
    cin >> a >> b >> w, a--, b--;
    ed[i] = {a, b, w};
  }
  int c = minimumSpanningTree();
  cout << c << "\n";
}
