#include <bits/stdc++.h>

using namespace std;

struct fenwick_tree {
  int n;
  vector<int> a, f;
  fenwick_tree(int n = 0) : n(n), a(n), f(n + 1) {}
  fenwick_tree(vector<int> & a) : fenwick_tree(a.size()) {
    for (int i = 0; i < n; i++)
      setValue(i, a[i]);
  }
  void changeValue(int i, int d) {
    for (a[i++] += d; i <= n; i += i & -i)
      f[i] += d;
  }
  void setValue(int i, int v) {
    changeValue(i, v - a[i]);
  }
  int getSum(int i) {
    int s = 0;
    for (i++; i; i -= i & -i)
      s += f[i];
    return s;
  }
  // get the sum of the range [l, r[
  int getSum(int l, int r) {
    return getSum(r - 1) - getSum(l - 1);
  }
};

int main() {
  int n, q;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++)
    cin >> a[i];
  cin >> q;
  vector<int> ql(q), qr(q), qu(q), r(q);
  for (int i = 0; i < q; i++)
    cin >> ql[i] >> qr[i], ql[i]--, qr[i]--, qu[i] = i;
  sort(qu.begin(), qu.end(), [&](int a, int b){ return qr[a] < qr[b]; });
  fenwick_tree f(n);
  vector<int> p(1000001, -1);
  int j = 0;
  for (int i = 0; i < q; i++) {
    for (; j <= qr[qu[i]]; j++) {
      if (p[a[j]] != -1)
        f.setValue(p[a[j]], 0);
      f.setValue(j, 1);
      p[a[j]] = j;
    }
    r[qu[i]] = f.getSum(ql[qu[i]], qr[qu[i]] + 1);
  }
  for (int i = 0; i < q; i++)
    cout << r[i] << "\n";
}
