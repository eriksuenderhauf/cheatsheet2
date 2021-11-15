//for extra speed use follwoing custom complex type
struct cpx {
  double a=0,b=0;
  cpx(){}
  cpx(double a):a(a){}
  cpx(double a, double b):a(a),b(b){}
  double modsq() {
    return a * a + b * b;
  }
  cpx bar() {
    return cpx(a, -b);
  }
  cpx operator /=(int n) {
    a /= n, b /= n;
    return *this;
  }
};
cpx operator +(cpx a, cpx b) {
  return cpx(a.a + b.a, a.b + b.b);
}
cpx operator -(cpx a, cpx b) {
  return cpx(a.a - b.a, a.b - b.b);
}
cpx operator *(cpx a, cpx b) {
  return cpx(a.a * b.a - a.b * b.b, a.a * b.b + a.b * b.a);
}
cpx operator /(cpx a, cpx b) {
  cpx r = a * b.bar();
  return cpx(r.a / b.modsq(), r.b / b.modsq());
}
using cd = cpx;
//otherwise use
//using cd = complex<double>;

void fft(vector<cd> & a, bool inv) {
  int n = a.size();
  for (int i = 1, j = 0; i < n; i++) {
    int bit = n >> 1;
    for (j ^= bit; !(j&bit); j ^= (bit>>=1));
    if (i < j)
      swap(a[i], a[j]);
  }
  for (int len = 2; len <= n; len <<= 1) {
    double ang = 2 * M_PI / len * (inv ? -1 : 1);
    cd wlen(cos(ang), sin(ang));
    for (int i = 0; i < n; i += len) {
      cd w(1);
      for (int j = 0; j < len / 2; j++) {
        cd u = a[i+j], v = a[i+j+len/2] * w;
        a[i+j] = u + v; a[i+j+len/2] = u - v;
        w = w*wlen;
      }
    }
  }
  if (inv)
    for (cd & x : a)
      x /= n;
}

void mul(vector<cd> & a, vector<cd> & b) {
  int n = 1;
  while ((1 << n) < max(a.size(), b.size())) n++;
  n++;
  a.resize(1 << n);
  b.resize(1 << n);
  fft(a, false), fft(b, false);
  for (int i = 0; i < (int) a.size(); i++)
    a[i] = a[i] * b[i];
  fft(a, true);
}
