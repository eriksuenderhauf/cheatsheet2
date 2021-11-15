#include <bits/stdc++.h>

using namespace std;

struct lis {
  int n, l = 0;
  vector<int> v, e, p;
  lis(vector<int> & a) : n(a.size()), v(n), e(n), p(n) {
    for (int i = 0; i < n; i++) {
      int j = lower_bound(v.begin(), v.begin() + l, a[i]) - v.begin();
      v[j] = a[i]; e[j] = i; p[i] = (j > 0 ? e[j - 1] : -1);
      l = max(l, j + 1);
    }
  }
};

int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++)
    cin >> a[i];
  lis l(a);
  cout << l.l << "\n";
  vector<int> r;
  int c = (l.l > 0 ? l.e[l.l - 1] : -1);
  while (c != -1)
    r.push_back(c), c = l.p[c];
  reverse(r.begin(), r.end());
  for (int i = 0; i < r.size(); i++)
    cout << r[i] + 1 << (i < r.size() - 1 ? " " : "\n");
}
