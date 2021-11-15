#include <bits/stdc++.h>

using namespace std;

#define MAXN 100000
#define left(i) (2 * (i) + 1)
#define right(i) (2 * (i) + 2)
#define parent(i) (((i) - 1) / 2)

const int logmaxn = (int) log2(MAXN) + 1;
const int ts = 1 << (logmaxn + 1), to = (1 << logmaxn) - 1;

// the data with default values
struct data {
  int v = 0, l = 1 << logmaxn, r = 0;
};

// the operation with default values
// this default operation applies a * v + b to every element v
struct operation {
  int a = 1, b = 0;
};

int n, a[MAXN];
data t[ts];
operation o[ts];

// combine the data from different branches
data combine(data l, data r) {
  return {l.v + r.v, min(l.l, r.l), max(l.r, r.r)};
}

// apply an operation on top of an other operation
operation combine(operation ot, operation ob) {
  return {ot.a * ob.a, ot.b + ot.a * ob.b};
}

// apply an operation on a range with data
data apply(operation ot, data d) {
  return {ot.a * d.v + ot.b * (d.r - d.l), d.l, d.r};
}

data getValue(int x) {
  return apply(o[x], t[x]);
}

void calcValue(int x) {
  t[x] = combine(getValue(left(x)), getValue(right(x)));
}

void propagate(int x) {
  o[left(x)] = combine(o[x], o[left(x)]);
  o[right(x)] = combine(o[x], o[right(x)]);
  o[x] = operation();
}

// query the data on the range [a, b[
data query(int a, int b, int x = 0, int l = 0, int r = 1 << logmaxn) {
  if (a <= l && r <= b)
    return getValue(x);
  if (b <= l || r <= a)
    return data();
  int m = (l + r) / 2;
  propagate(x);
  data d = combine(query(a, b, left(x), l, m), query(a, b, right(x), m, r));
  calcValue(x);
  return d;
}

// apply an operation on the range [a, b[
void apply(int a, int b, operation v, int x = 0, int l = 0, int r = 1 << logmaxn) {
  if (a <= l && r <= b) {
    o[x] = combine(v, o[x]);
    return;
  }
  if (b <= l || r <= a)
    return;
  int m = (l + r) / 2;
  propagate(x);
  apply(a, b, v, left(x), l, m);
  apply(a, b, v, right(x), m, r);
  calcValue(x);
}

// get the data for the i-th position
data getData(int i) {
  if (i < n)
    return {a[i], i, i + 1};
  else
    return {0, i, i + 1};
}

void init() {
  for (int i = 0; i < (1 << logmaxn); i++)
    t[to + i] = getData(i);
  for (int x = to - 1; x >= 0; x--)
    calcValue(x);
}

int main() {
  int q, t, l, r, f, o;
  cin >> n >> q;
  for (int i = 0; i < n; i++)
    cin >> a[i];
  init();
  for (int i = 0; i < q; i++) {
    cin >> t >> l >> r, l--;
    if (t == 1) {
      cin >> f >> o;
      apply(l, r, {f, o});
    } else {
      data d = query(l, r);
      cout << d.v << "\n";
    }
  }
}
