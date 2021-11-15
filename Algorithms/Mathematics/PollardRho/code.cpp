typedef unsigned long long ul;
ul pollard(ul n) { // return some nontrivial factor of n
  auto f = [n](ul x) { return x * x % n + 1; };
  ul x = 0, y = 0, t = 30, prd = 2, i = 1, q;
  while (t++ % 40 || gcd(prd, n) == 1) {
    if (x == y) x = ++i, y = f(x);
    if ((q = prd * (max(x,y)-min(x,y)) % n)) prd = q;
    x = f(x), y = f(f(y));
  }
  return gcd(prd, n);
}
void factor_rec(ul n, map<ul,int>& cnt) {
  if (n == 1) return;
  if (is_prime(n)) { ++cnt[n]; return; }
  ul u = pollard(n);
  factor_rec(u,cnt), factor_rec(n/u,cnt);
}
vector<pair<ul,int>> factor(ul n) {
  map<ul,int> cnt; factor_rec(n,cnt);
  return vector<pair<ul,int>>(all(cnt));
}