#include <bits/stdc++.h>

using namespace std;

#define MAXN 100000
#define MAXQ 100000

const int logmaxn = (int) log2(MAXN) + 1;

// the data with default values
struct data {
  int v = 0, l = 1 << logmaxn, r = 0;
};

// the operation with default values
// this default operation applies a * v + b to every element v
struct operation {
  int a = 1, b = 0;
};

struct node {
  node * l = 0, * r = 0;
  data t;
  operation o;
};

int n, v, a[MAXN];
node * root[MAXQ + 1];

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

data getValue(node * x) {
  if (x == 0)
    return data();
  return apply(x->o, x->t);
}

void calcValue(node * x) {
  x->t = combine(getValue(x->l), getValue(x->r));
}

node * copyNode(node * x) {
  node * r = new node();
  r->l = x->l;
  r->r = x->r;
  r->t = x->t;
  r->o = x->o;
  return r;
}

void newRoot(int l = -1) {
  v++;
  if (l < 0)
    l += v;
  root[v] = copyNode(root[l]);
  root[v]->t = {0, 0, 1 << logmaxn};
}

void propagate(node * x, int l, int m, int r) {
  if (x->l == 0)
    x->l = new node(), x->l->t = {0, l, m};
  else
    x->l = copyNode(x->l);
  if (x->r == 0)
    x->r = new node(), x->r->t = {0, m, r};
  else
    x->r = copyNode(x->r);
  x->l->o = combine(x->o, x->l->o);
  x->r->o = combine(x->o, x->r->o);
  x->o = operation();
}

// query the data on the range [a, b[
data query(node * x, int a, int b, int l = 0, int r = 1 << logmaxn) {
  if (a <= l && r <= b)
    return getValue(x);
  if (b <= l || r <= a)
    return data();
  int m = (l + r) / 2;
  propagate(x, l, m, r);
  data d = combine(query(x->l, a, b, l, m), query(x->r, a, b, m, r));
  calcValue(x);
  return d;
}

data query(int a, int b) {
  newRoot();
  return query(root[v], a, b);
}

// apply an operation on the range [a, b[
void apply(node * x, int a, int b, operation o, int l = 0, int r = 1 << logmaxn) {
  if (a <= l && r <= b) {
    x->o = combine(o, x->o);
    return;
  }
  if (b <= l || r <= a)
    return;
  int m = (l + r) / 2;
  propagate(x, l, m, r);
  apply(x->l, a, b, o, l, m);
  apply(x->r, a, b, o, m, r);
  calcValue(x);
}

void apply(int a, int b, operation o) {
  newRoot();
  apply(root[v], a, b, o);
}

// get the data for the i-th position
data getData(int i) {
  if (i < n)
    return {a[i], i, i + 1};
  else
    return {0, i, i + 1};
}

// initialize only when having an initial configuration
void init(node * x, int l = 0, int r = 1 << logmaxn) {
  if (l + 1 == r) {
    x->t = getData(l);
    return;
  }
  int m = (l + r) / 2;
  x->l = new node();
  x->r = new node();
  init(x->l, l, m);
  init(x->r, m, r);
  calcValue(x);
}

void init() {
  root[0] = new node();
  root[0]->t = {0, 0, 1 << logmaxn};
  // init(root[0]);
  for (int i = 0; i < n; i++)
    apply(root[0], i, i + 1, {0, a[i]});
}

int main() {
  int q, t, l, r, f, o;
  cin >> n >> q;
  for (int i = 0; i < n; i++)
    cin >> a[i];
  init();
  for (int i = 0; i < q; i++) {
    cin >> t >> l;
    if (t != 3) {
      l--;
      cin >> r;
    }
    if (t == 1) {
      cin >> f >> o;
      apply(l, r, {f, o});
    } else if (t == 2) {
      data d = query(l, r);
      cout << d.v << "\n";
    } else {
      newRoot(l);
    }
  }
}
