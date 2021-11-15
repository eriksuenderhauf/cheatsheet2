#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
using namespace std;
typedef unsigned long long ul;
ul expmod(ul x, ul y, ul m) {
  ul r = 1;
  for (; y; y /= 2, x = x * x % m)
    if (y & 1)
      r = r * x % m;
  return r;
}
bool Miller(ul p, ul s, int a) {
  if(p == a) return 1;
  ul mod = expmod(a, s, p); //a^s
  for(; s - p + 1 && mod - 1 && mod - p + 1; s *= 2) mod = mod * mod % p;  //mod^2
  return mod == p - 1 || s % 2;
}
bool isprime(ul n) {
  if(n < 2) return 0;
  if(n % 2 == 0) return n == 2;
  ul s = n - 1;
  while(s % 2 == 0) s /= 2;
  return Miller(n, s, 2) && Miller(n, s, 7) && Miller(n, s, 61);
} 

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
  if (isprime(n)) { ++cnt[n]; return; }
  ul u = pollard(n);
  factor_rec(u,cnt), factor_rec(n/u,cnt);
}
vector<pair<ul,int>> factor(ul n) {
  map<ul,int> cnt; factor_rec(n,cnt);
  return vector<pair<ul,int>>(all(cnt));
}
int main() {
  auto f = factor(1234567654ul);
  for (auto [x, y]: f) {
    cout << x << " " << y << endl;
  }
}