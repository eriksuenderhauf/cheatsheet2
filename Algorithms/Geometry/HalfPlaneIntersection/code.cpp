struct plane {
  pt p, d;
  ld phi;
  plane() {}
  plane(pt a, pt b) : p(a), d(b - a) {
    phi = atan2(d.y, d.x);
  }
  bool out(pt x) const {
    return cross(d, x - p) < -eps;
  }
  bool operator<(const plane& x) const {
    return abs(phi - x.phi) < eps ? out(x.p) : phi < x.phi;
  }
  bool operator==(const plane& x) const {
    return abs(phi - x.phi) < eps;
  }
  friend pt sect(const plane& x, const plane& y) {
    return x.p + x.d * (cross(y.p - x.p, y.d) / cross(x.d, y.d));
  }
};
vector<pt> solve(vector<plane> a) {
  a.pb(plane(pt(inf, inf), pt(-inf, inf)));
  a.pb(plane(pt(-inf, inf), pt(-inf, -inf)));
  a.pb(plane(pt(-inf, -inf), pt(inf, -inf)));
  a.pb(plane(pt(inf, -inf), pt(inf, inf)));
  sort(all(a));
  a.erase(unique(all(a)), a.end());
  int n = sz(a);
  deque<plane> pq;
  for (int i = 0; i < n; i++) {
    while (sz(pq) > 1 && a[i].out(sect(pq[sz(pq)-1], pq[sz(pq)-2])))
      pq.pop_back();
    while (sz(pq) > 1 && a[i].out(sect(pq[0], pq[1])))
      pq.pop_front();
    pq.push_back(a[i]);
  }
  while (sz(pq) > 2 && pq[0].out(sect(pq[sz(pq)-1], pq[sz(pq)-2])))
    pq.pop_back();
  while (sz(pq) > 2 && pq.back().out(sect(pq[0], pq[1])))
    pq.pop_front();
  if (sz(pq) < 3)
    return {};
  vector<pt> ret(sz(pq));
  for (int i = 0; i < sz(pq); i++)
    ret[i] = sect(pq[i], pq[(i+1) % sz(pq)]);
  return ret;
}