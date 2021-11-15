struct alien {
static const int N = 1005;
vector<vector<ll>> C;
int dp[N], cnt[N];
int n, k, q[N], par[N];
alien(int n, int k, vector<vector<ll>> & C) : n(n), k(k), C(c);
int gt(int i, int j, bool mi = 1) {
  int lo = j+1, hi = n;
  bool fl = mi || (cnt[i] > cnt[j]);
  while (lo <= hi) {
    int mi = (lo + hi) / 2;
    ll l = dp[i] + C[i+1][mi];
    ll r = dp[j] + C[j+1][mi];
    if (l > r || (l == r && fl))
      lo = mi + 1;
    else
      hi = mi - 1;
  }
  return lo;
}
int solve(ll x, bool mi = 1) {
  for (int i = 1, l = 0, r = 0; i <= n; i++) {
    while (l<r && gt(q[l], q[l+1], mi) <= i)
      l++;
    dp[i] = dp[q[l]] + C[q[l]+1][i] + x;
    cnt[i] = cnt[q[l]] + 1;
    par[i] = q[l];
    while (l<r && gt(q[r-1], q[r], mi) >= gt(q[r], i)) 
      r--;
    q[++r] = i;
  }
  return cnt[n];
}
vector<int> reconstruct(ll x) {
  vector<int> lo, hi, ret;
  solve(x, 1);
  for (int u = n; u != 0; u = par[u])
    lo.pb(u);
  if (sz(lo) == k) return lo;
  solve(x, 0);
  for (int u = n; u != 0; u = par[u])
    hi.pb(u);
  if (sz(hi) == k) return hi;
  lo.pb(0); reverse(lo.begin(), lo.end());
  hi.pb(0); reverse(hi.begin(), hi.end());
  for (int cl=1, ch=1; i < sz(hi); ch++) {
    while (cl < sz(lo) && lo[cl] < hi[ch])
      ret.pb(lo[cl++]);
    if (lo[cl-1] <= hi[ch-1] && sz(hi) - 1 - k == ch - cl) {
      for (; cl < sz(hi); cl++)
        ret.pb(hi[cl]);
      break;
    }
  }
  return ret;
}
// solves the maximization problem
void doDp() {
  ll lo = -3*inf, hi = 3*inf, ans = 0;
  while (lo <= hi) {
    ll mi = lo+(hi-lo) / 2;
    if (solve(mi) <= k)
      lo = mi + 1, ans = dp[n];
    else
      hi = mi - 1;
  }
  return ans - k * hi;
}
};