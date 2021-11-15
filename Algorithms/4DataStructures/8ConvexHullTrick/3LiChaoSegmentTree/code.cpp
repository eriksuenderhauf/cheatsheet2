struct Line {
  ll m, n;
  Line() : m(0), n(LLONG_MIN) {}
  Line(ll _m, ll _n) : m(_m), n(_n) {}
  ll get(ll x) { return m*x + n; }
  bool majorize(ll l, ll r, Line x) {
    return get(l) >= x.get(l) && get(r) >= x.get(r);
  }
};
struct LiChao {
  LiChao *c[2] = {0, 0}; Line d = Line();
  ll qry(ll l, ll r, ll x) {
    ll ret = d.get(x), m = l + (r - l) / 2;
    if (x <= m) {
      if (c[0]) ret = max(ret, c[0]->qry(l, m, x));
    } else {
      if (c[1]) ret = max(ret, c[1]->qry(m + 1, r, x));
    }
    return ret;
  }
  void modify(ll l, ll r, Line v) {
    if (v.majorize(l, r, d)) swap(d, v);
    if (d.majorize(l, r, v)) return;
    if (d.get(l) < v.get(l)) swap(d, v);
    ll m = l + (r - l) / 2;
    if (d.get(m) < v.get(m)) {
      swap(d, v);
      if (!c[0]) c[0] = new LiChao();
      c[0]->modify(l, m, v);
    } else {
      if (!c[1]) c[1] = new LiChao();
      c[1]->modify(m + 1, r, v);
    }
  }
  void upd(ll l, ll r, ll x, ll y, Line v) {
    if (r < x || y < l) return;
    if (x <= l && r <= y) return modify(l, r, v);
    ll m = l + (r - l) / 2;
    if (x <= m) {
      if (!c[0]) c[0] = new LiChao();
      c[0]->upd(l, m, x, y, v);
    }
    if (y > m) {
      if (!c[1]) c[1] = new LiChao();
      c[1]->upd(m + 1, r, x, y, v);
    }
  }
};