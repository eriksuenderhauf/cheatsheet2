// Inspired by https://codeforces.com/blog/entry/63903

template <int MOD=1000000007>
struct mint {
  int value;
  static const int MOD_value = MOD;

  mint(long long v = 0) { value = v % MOD; if (value < 0) value += MOD;}
  mint(long long a, long long b) : value(0){ *this += a; *this /= b;}

  mint& operator+=(mint const& b) {value += b.value; if (value >= MOD) value -= MOD; return *this;}
  mint& operator-=(mint const& b) {value -= b.value; if (value < 0) value += MOD;return *this;}
  mint& operator*=(mint const& b) {value = (long long)value * b.value % MOD;return *this;}

  friend mint mexp(mint a, long long e) {
    mint res = 1; while (e) { if (e&1) res *= a; a *= a; e >>= 1; }
    return res;
  }
  friend mint inv(mint a) { return mexp(a, MOD - 2); }

  mint& operator/=(mint const& b) { return *this *= inverse(b); }
  friend mint operator+(mint a, mint const b) { return a += b; }
  friend mint operator-(mint a, mint const b) { return a -= b; }
  friend mint operator-(mint const a) { return 0 - a; }
  friend mint operator*(mint a, mint const b) { return a *= b; }
  friend mint operator/(mint a, mint const b) { return a /= b; }
  friend bool operator==(mint const& a, mint const& b) {return a.value == b.value;}
  friend bool operator!=(mint const& a, mint const& b) {return a.value != b.value;}
  friend ostream& operator<<(ostream& os, mint const& a) {return os << a.value;}
  friend istream& operator>>(istream& is, mint const& a) {
      is >> a.value; a.value %= MOD; if (a.value < 0) a.value += MOD; return is;}
};
typedef mint<> M;
M inv(int a) { return inv(M(a)); }
