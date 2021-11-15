#include <bits/stdc++.h>

using namespace std;

#define MAXN 100000
#define LSOne(S) (S & (-S))

int n, a[MAXN], f[MAXN + 1];

void change(int i, int d) {
  for (i++; i <= n; i += LSOne(i))
    f[i] += d;
}

void init() {
  for (int i = 0; i < n; i++)
    change(i, a[i]);
}

void setValue(int i, int v) {
  change(i, v - a[i]);
  a[i] = v;
}

int getSum(int i) {
  int s = 0;
  for (i++; i; i -= LSOne(i))
    s += f[i];
  return s;
}

// get the sum of the range [l, r]
int getSum(int l, int r) {
  return getSum(r) - getSum(l - 1);
}

int main() {
  int q, t, l, r;
  cin >> n >> q;
  for (int i = 0; i < n; i++)
    cin >> a[i];
  init();
  for (int i = 0; i < q; i++) {
    cin >> t >> l >> r, l--;
    if (t == 1)
      setValue(l, r);
    else
      cout << getSum(l, r - 1) << "\n";
  }
}
