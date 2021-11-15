#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct segment_tree {
  // data (sum and length of a segment)
  struct data {
    ll s = 0, t = 0, l = 0;
  };
  // operation on the data (x -> a * x + b)
  struct operation {
    int a = 1, b = 0;
  };
  // alternatively use typedefs for simpler data and operations
  // combine the data from different segments
  static data combine(data dl, data dr) {
    return {dl.s + dr.s, dl.t + dr.t, dl.l + dr.l};
  }
  // calculate the result of an operation on the data
  static data calculate(operation o, data d) {
    return {o.a * d.s + o.b * d.l, o.a * o.a * d.t + 2 * o.a * d.s * o.b + o.b * o.b * d.l, d.l};
  }
  // merge an operation onto another operation
  static operation merge(operation ot, operation ob) {
    return {ot.a * ob.a, ot.b + ot.a * ob.b};
  }
  int n, h;
  vector<data> t;
  vector<operation> o;
  segment_tree(int n = 0) : n(n), h(32 - __builtin_clz(n)), t(2 * n), o(n) {}
  segment_tree(vector<data> & a) : segment_tree(a.size()) {
    for (int i = 0; i < n; i++)
      t[i + n] = a[i];
    for (int x = n - 1; x > 0; x--)
      t[x] = combine(t[x << 1], t[x << 1 | 1]);
  }
  void apply(int x, operation op) {
    t[x] = calculate(op, t[x]);
    if (x < n)
      o[x] = merge(op, o[x]);
  }
  void push(int x) {
    for (int s = h; s > 0; s--) {
      int c = x >> s;
      apply(c << 1, o[c]);
      apply(c << 1 | 1, o[c]);
      o[c] = operation();
    }
  }
  void build(int x) {
    while (x >>= 1)
      t[x] = calculate(o[x], combine(t[x << 1], t[x << 1 | 1]));
  }
  // set the data at the position i
  void setValue(int i, data d) {
    i += n;
    push(i);
    t[i] = d;
    build(i);
  }
  // query the data on the range [l, r[
  data query(int l, int r) {
    l += n; r += n;
    push(l); push(r - 1);
    data dl, dr;
    for (; l < r; l >>= 1, r >>= 1) {
      if (l & 1)
        dl = combine(dl, t[l++]);
      if (r & 1)
        dr = combine(t[--r], dr);
    }
    return combine(dl, dr);
  }
  // apply an operation on the range [l, r[
  void apply(int l, int r, operation op) {
    l += n; r += n;
    push(l); push(r - 1);
    int xl = l, xr = r;
    for (; l < r; l >>= 1, r >>= 1) {
      if (l & 1)
        apply(l++, op);
      if (r & 1)
        apply(--r, op);
    }
    build(xl); build(xr - 1);
  }
};

int main() {
  int t;
  cin >> t;
  for (int tt = 0; tt < t; tt++) {
    cout << "Case " << tt + 1 << ":\n";
    int n, q, o, l, r, v;
    cin >> n >> q;
    vector<segment_tree::data> a(n);
    for (int i = 0; i < n; i++)
      cin >> a[i].s, a[i].t = a[i].s * a[i].s, a[i].l = 1;
    segment_tree st(a);
    for (int i = 0; i < q; i++) {
      cin >> o >> l >> r, l--;
      if (o == 0 || o == 1) {
        cin >> v;
        st.apply(l, r, {o, v});
      } else {
        ll s = st.query(l, r).t;
        cout << s << "\n";
      }
    }
  }
}
