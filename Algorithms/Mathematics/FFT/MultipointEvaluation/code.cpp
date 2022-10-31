Poly evaluate(const Poly& x, Poly b) {
  int n = max(sz(x) + 1, sz(b));
  vector<Poly> p(2 * n), q(2 * n);
  for (int i = 0; i < n; i++)
    q[i + n] = {i < sz(b) ? mod - b[i] : 0, 1};
  for (int i = n - 1; i > 0; i--)
    q[i] = q[2 * i] * q[2 * i + 1];
  reverse(all(q[1])); q[1] = invert(q[1], sz(q[1]));
  reverse(all(q[1]));
  p[1] = range(x * q[1], sz(q[1]) - 1, 2 * n);
  p[1].resize(2 * n - sz(q[1]) + 1);
  for (int i = 2; i < sz(b) + n; i++)
    p[i] = range(p[i / 2] * q[i ^ 1], sz(q[i ^ 1]) - 1, sz(p[i / 2]));
  for (int i = 0; i < sz(b); i++)
    b[i] = p[i + n][0];
  return b;
}