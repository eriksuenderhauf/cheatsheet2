//for extra speed use follwoing custom complex type
struct cpx {
  double a=0,b=0;
  cpx(){}
  cpx(double a):a(a){}
  cpx(double a, double b):a(a),b(b){}
  double len() {
    return a * a + b * b;
  }
  cpx bar() {
    return cpx(a, -b);
  }
  cpx operator/=(int n) {
    a /= n, b /= n;
    return *this;
  }
};
cpx operator+(cpx a, cpx b) {
  return cpx(a.a + b.a, a.b + b.b);
}
cpx operator-(cpx a, cpx b) {
  return cpx(a.a - b.a, a.b - b.b);
}
cpx operator*(cpx a, cpx b) {
  return cpx(a.a * b.a - a.b * b.b, a.a * b.b + a.b * b.a);
}
cpx operator/(cpx a, cpx b) {
  cpx r = a * b.bar();
  return cpx(r.a / b.len(), r.b / b.len());
}
using cd = cpx;
//using cd = complex<double>;

void fft(vector<cd> & a, int inv) {
  int n = sz(a);
  for (int i = 1, j = 0; i < n; i++) {
    int bit = n >> 1;
    for (j ^= bit; !(j&bit); j ^= (bit>>=1));
    if (i < j)
      swap(a[i], a[j]);
  }
  for (int l = 2; l <= n; l *= 2) {
    double ang = 2 * pi / l * (inv ? -1 : 1);
    cd wl(cos(ang), sin(ang));
    for (int i = 0; i < n; i += l) {
      cd w(1);
      for (int j = i; j < i + l / 2; j++) {
        cd u = a[j], v = a[j + l / 2] * w;
        a[j] = u + v; a[j + l / 2] = u - v;
        w = w * wl;
      }
    }
  }
  if (inv)
    for (cd & x : a)
      x /= n;
}