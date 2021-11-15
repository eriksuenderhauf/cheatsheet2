#include <bits/stdc++.h>

using namespace std;

#define MAXN 100000

int n, cs, ms, cc, s[MAXN], cp[MAXN], cd[MAXN];
bool u[MAXN];
vector<int> e[MAXN];

void findCentroid(int i, int p = -1) {
  int cms = 0;
  s[i] = 1; cp[i] = p;
  for (int j : e[i]) {
    if (u[j] || j == p)
      continue;
    findCentroid(j, i);
    cms = max(cms, s[j]);
    s[i] += s[j];
  }
  cms = max(cms, cs - s[i]);
  if (cms < ms)
    ms = cms, cc = i;
}

void findCentroidDecomposition(int i, int p = -1, int d = 0) {
  cs = s[i]; ms = cs + 1;
  findCentroid(i);
  i = cc; cd[i] = d; u[i] = true;
  if (cp[i] != -1)
    s[cp[i]] = cs - s[i];
  s[i] = cs; cp[i] = p;
  for (int j : e[i])
    if (!u[j])
      findCentroidDecomposition(j, i, d + 1);
}

void centroidDecomposition(int i = 0) {
  s[i] = n;
  findCentroidDecomposition(i);
}

int main() {
  cin >> n;
  int a, b;
  for (int i = 0; i < n - 1; i++) {
    cin >> a >> b, a--, b--;
    e[a].push_back(b);
    e[b].push_back(a);
  }
  centroidDecomposition();
  for (int i = 0; i < n; i++)
    cout << i + 1 << " " << cp[i] + 1 << " " << cd[i] << " " << s[i] << "\n";
}
