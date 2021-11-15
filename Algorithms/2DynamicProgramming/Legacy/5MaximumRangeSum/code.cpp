#define MAXN 100000

int n, a[MAXN];

// get the maximum sum of a range
int getMaximumRangeSum() {
  int s = 0, m = 0;
  for (int i = 0; i < n; i++) {
    s = max(0, s + a[i]);
    m = max(m, s);
  }
  return m;
}
