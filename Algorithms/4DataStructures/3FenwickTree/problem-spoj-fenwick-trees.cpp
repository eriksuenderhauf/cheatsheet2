#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct fenwick_tree {
  int n;
  vector<ll> a, f;
  fenwick_tree(int n = 0) : n(n), a(n), f(n + 1) {}
  fenwick_tree(vector<int> & a) : fenwick_tree(a.size()) {
    for (int i = 0; i < n; i++)
      setValue(i, a[i]);
  }
  void changeValue(int i, ll d) {
    for (a[i++] += d; i <= n; i += i & -i)
      f[i] += d;
  }
  void setValue(int i, ll v) {
    changeValue(i, v - a[i]);
  }
  ll getSum(int i) {
    ll s = 0;
    for (i++; i; i -= i & -i)
      s += f[i];
    return s;
  }
  // get the sum of the range [l, r[
  ll getSum(int l, int r) {
    return getSum(r - 1) - getSum(l - 1);
  }
};

int main() {
  int n, q, l, r;
  char t;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++)
    cin >> a[i];
  fenwick_tree f(a);
  cin >> q;
  for (int i = 0; i < q; i++) {
    cin >> t >> l >> r, l--;
    if (t == 'u')
      f.changeValue(l, r);
    else
      cout << f.getSum(l, r) << "\n";
  }
}
