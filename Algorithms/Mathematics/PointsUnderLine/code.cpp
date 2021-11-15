ll prog(ll a, ll b, ll c) {
  return c * a + b * c * (c + 1) / 2;
}
ll sum(ll a, ll b, ll c, ll d) {
  if ((a + b * d) / c == 0 || d < 1)
    return 0;
  ll r = prog(a < 0 ? (a - c + 1) / c : a / c, b / c, d);
  if (b % c != 0) {
    a = (a % c + c) % c, b = (b % c + c) % c;
    r += sum((a + b * d) % c + b - c, c, b, (a + b * d) / c);
  }
  return r;
}