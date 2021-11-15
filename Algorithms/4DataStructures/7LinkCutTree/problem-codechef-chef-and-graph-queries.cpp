#include <bits/stdc++.h>

using namespace std;

struct link_cut_tree {
  // data (sum and length of a segment)
  struct data {
    int e = 1000000000;
  };
  // operation on the data (x -> a * x + b)
  struct operation {
    int a = 1, b = 0;
  };
  // alternatively use typedefs for simpler data and operations
  // combine the data from different segments
  static data combine(data dl, data dr) {
    return {min(dl.e, dr.e)};
  }
  // calculate the result of an operation on the data
  static data calculate(operation o, data d) {
    return d;
  }
  // merge an operation onto another operation
  static operation merge(operation ot, operation ob) {
    return {ot.a * ob.a, ot.b + ot.a * ob.b};
  }
  struct node {
    node *p = 0, *c[2] = {0, 0};
    bool r = false;
    data d, t;
    operation o;
  };
  vector<node> v;
  link_cut_tree(int n) : v(n) {}
  bool isRoot(node *x) {
    return !x->p || x->p->c[0] != x && x->p->c[1] != x;
  }
  int direction(node *x) {
    return x->p && x->p->c[1] == x;
  }
  data getData(node *x) {
    return x ? x->t : data();
  }
  void fix(node *x) {
    for (int i = 0; i < 2; i++)
      if (x->c[i])
        x->c[i]->p = x;
    x->t = combine(getData(x->c[0]), combine(x->d, getData(x->c[1])));
  }
  void apply(node *x, bool r, operation o) {
    x->r ^= r;
    x->d = calculate(o, x->d);
    x->t = calculate(o, x->t);
    x->o = merge(o, x->o);
  }
  void push(node *x) {
    if (x->r)
      swap(x->c[0], x->c[1]);
    for (int i = 0; i < 2; i++)
      if (x->c[i])
        apply(x->c[i], x->r, x->o);
    x->r = false;
    x->o = operation();
  }
  void rotate(node *x) {
    node *p = x->p;
    int d = direction(x);
    p->c[d] = x->c[!d];
    if (!isRoot(p))
      p->p->c[direction(p)] = x;
    x->p = p->p;
    x->c[!d] = p;
    fix(p);
    fix(x);
  }
  void splay(node *x) {
    while (!isRoot(x)) {
      if (!isRoot(x->p))
        push(x->p->p);
      push(x->p); push(x);
      if (!isRoot(x->p)) {
        if (direction(x) == direction(x->p))
          rotate(x->p);
        else
          rotate(x);
      }
      rotate(x);
    }
    push(x);
  }
  node* outermost(node *x, int d) {
    push(x);
    while (x->c[d]) {
      x = x->c[d];
      push(x);
    }
    splay(x);
    return x;
  }
  node* expose(node *x) {
    node *r = 0;
    for (node *p = x; p; p = p->p) {
      splay(p);
      p->c[1] = r;
      fix(p);
      r = p;
    }
    splay(x);
    return r;
  }
  // get the root of the tree containing x
  int findRoot(int x) {
    expose(&v[x]);
    return outermost(&v[x], 0) - &v[0];
  }
  // make x the root of the tree
  void makeRoot(int x) {
    expose(&v[x]);
    v[x].r ^= 1;
  }
  // get the parent of x
  int getParent(int x) {
    expose(&v[x]);
    return v[x].c[0] ? outermost(v[x].c[0], 1) - &v[0] : -1;
  }
  // set the parent of x to y
  void link(int x, int y) {
    makeRoot(x);
    v[x].p = &v[y];
  }
  // cut the link between x and its parent
  void cut(int x) {
    expose(&v[x]);
    v[x].c[0]->p = 0;
    v[x].c[0] = 0;
    fix(&v[x]);
  }
  // cut the link between x and y
  void cut(int x, int y) {
    makeRoot(y);
    cut(x);
  }
  bool inSameComponent(int x, int y) {
    return findRoot(x) == findRoot(y);
  }
  // calculate the lowest common ancestor of x and y
  int lca(int x, int y) {
    if (x == y)
      return x;
    expose(&v[x]);
    node *z = expose(&v[y]);
    return v[x].p ? z - &v[0] : -1;
  }
  // query the data along the path from x to y
  data query(int x, int y) {
    makeRoot(x);
    expose(&v[y]);
    return v[y].t;
  }
  // apply an operation along the path from x to y
  void apply(int x, int y, operation o) {
    makeRoot(x);
    expose(&v[y]);
    apply(&v[y], false, o);
  }
};

struct fenwick_tree {
  int n;
  vector<int> a, f;
  fenwick_tree(int n = 0) : n(n), a(n), f(n + 1) {}
  fenwick_tree(vector<int> & a) : fenwick_tree(a.size()) {
    for (int i = 0; i < n; i++)
      setValue(i, a[i]);
  }
  void changeValue(int i, int d) {
    for (a[i++] += d; i <= n; i += i & -i)
      f[i] += d;
  }
  void setValue(int i, int v) {
    changeValue(i, v - a[i]);
  }
  int getSum(int i) {
    int s = 0;
    for (i++; i; i -= i & -i)
      s += f[i];
    return s;
  }
  // get the sum of the range [l, r[
  int getSum(int l, int r) {
    return getSum(r - 1) - getSum(l - 1);
  }
};

int main() {
  int t;
  cin >> t;
  for (int tt = 0; tt < t; tt++) {
    int n, m, q;
    cin >> n >> m >> q;
    link_cut_tree lct(n + m);
    fenwick_tree f(m);
    vector<int> ea(m), eb(m), ql(q), qr(q), qu(q), r(q);
    for (int i = 0; i < m; i++)
      cin >> ea[i] >> eb[i], ea[i]--, eb[i]--, lct.v[n + i].d.e = i;
    for (int i = 0; i < q; i++)
      cin >> ql[i] >> qr[i], ql[i]--, qr[i]--, qu[i] = i;
    sort(qu.begin(), qu.end(), [&](int a, int b) { return qr[a] < qr[b]; });
    int j = 0;
    for (int i = 0; i < q; i++) {
      for (; j <= qr[qu[i]]; j++) {
        if (ea[j] == eb[j])
          continue;
        if (lct.inSameComponent(ea[j], eb[j])) {
          link_cut_tree::data d = lct.query(ea[j], eb[j]);
          int k = d.e;
          lct.cut(ea[k], n + k);
          lct.cut(eb[k], n + k);
          f.setValue(k, 0);
        }
        lct.link(ea[j], n + j);
        lct.link(eb[j], n + j);
        f.setValue(j, 1);
      }
      r[qu[i]] = n - f.getSum(ql[qu[i]], qr[qu[i]] + 1);
    }
    for (int i = 0; i < q; i++)
      cout << r[i] << "\n";
  }
}
