/* use arrays if the TL is tight! */
#define ep emplace_back
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template<class T> struct treap {
  vector<int> L, R, prio;
  vector<T> val;
  int root = 0;
  treap() {
    L.ep(), R.ep(), prio.ep(), val.ep();
  }
  ll genRnd() {
    return uniform_int_distribution<int>(0,1e9)(rng);
  }
  int create(const T& v, ll p) {
    val.ep(v), L.ep(), R.ep(), prio.ep(p);
    return sz(val)-1;
  }
  void pushdown(int x) {
    if (!x) return;
  }
  void cmb(int x) {
    if (!x) return;
    pushdown(L[x]), pushdown(R[x]);
    // combine data from left and right child
  }
  void split(int cur, int &l, int &r, const T& v) {
    pushdown(cur);
    if (!cur)
      l = r = 0;
    else if (val[cur] < v) {
      int x = R[l = cur];
      split(R[cur], x, r, v);
      R[l] = x;
      cmb(l);
    } else {
      int x = L[r = cur];
      split(L[cur], l, x, v);
      L[r] = x;
      cmb(r);
    }
  }
  void merge(int &cur, int l, int r) {
    pushdown(l), pushdown(r);
    if (!l || !r)
      cur = !l ? r : l;
    else if (prio[l] > prio[r]) {
      int x = R[cur = l];
      merge(x, R[l], r);
      R[cur] = x;
    } else {
      int x = L[cur = r];
      merge(x, l, L[r]);
      L[cur] = x;
    }
    cmb(cur);
  }
  void add(int &cur, const T& v, ll p) {
    pushdown(cur);
    if (!cur) {
      cur = create(v, p);
    } else if (p > prio[cur]) {
      int nx = create(v, p);
      split(cur, L[nx], R[nx], v);
      cur = nx;
    } else {
      int x = val[cur] < v ? R[cur] : L[cur];
      add(x, v, p);
      if (val[cur] < v) R[cur] = x; else L[cur] = x;
    }
    cmb(cur);
  }
  void rem(int& cur, const T& v) {
    pushdown(cur);
    if (!(v < val[cur]) && !(val[cur] < v)) {
      merge(cur, L[cur], R[cur]);
    } else if (val[cur] < v) {
      int x = R[cur];
      rem(x, v);
      R[cur] = x;
    } else {
      int x = L[cur];
      rem(x, v);
      L[cur] = x;
    }
    cmb(cur);
  }
  void ins(const T& v) {
    add(root, v, genRnd());
  }
  void del(const T& v) {
    rem(root, v);
  }
  T qry(int x) {
    pushdown(x);
    return !R[x] ? val[x] : qry(R[x]);
  }
  T qryMax() {
    return qry(root);
  }
};