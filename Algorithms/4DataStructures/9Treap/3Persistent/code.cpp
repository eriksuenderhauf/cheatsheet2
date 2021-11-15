mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template<class T> struct treap {
  static const int N = 5e6 + 5;
  static const int inf = 1e9 + 7;
  int L[N], R[N], root[N], cnt = 0, cV = 0;
  ll p[N]; T val[N];
  int create(T v, ll pr) {
    val[++cnt] = v, L[cnt] = R[cnt] = 0;
    p[cnt] = pr;
    return cnt;
  }
  int copy(int k) {
    if (!k) return 0;
    L[++cnt] = L[k], R[cnt] = R[k];
    p[cnt] = p[k], val[cnt] = val[k];
    return cnt;
  }
  void split(int cur, int &l, int &r, T v) {
    if (!cur)
      l = r = 0;
    else if (val[cur] < v)
      split(R[cur], R[l = copy(cur)], r, v);
    else
      split(L[cur], l, L[r = copy(cur)], v);
  }
  void merge(int &cur, int l, int r) {
    if (!l || !r)
      cur = !l ? copy(r) : copy(l);
    else if (p[l] > p[r])
      merge(R[cur = copy(l)], R[l], r);
    else
      merge(L[cur = copy(r)], l, L[r]);
  }
  void add(int &cur, T v, ll pr) {
    if (!cur)
      cur = create(v, pr);
    else if (pr > p[cur]) {
      int nx = create(v, pr);
      split(cur, L[nx], R[nx], v);
      cur = nx;
    } else {
      int nx = copy(cur);
      add(v > val[nx] ? R[nx] : L[nx], v, pr);
      cur = nx;
    }
  }
  void insert(T v) {
    ll pr = uniform_int_distribution<int>(0,inf)(rng);
    add(root[++cV] = copy(root[cV-1]), v, pr);
  }
  T qryMx(int x) {//call: qryMx(root[version])
    return !R[x] ? val[x] : qryMx(R[x]);
  }
};