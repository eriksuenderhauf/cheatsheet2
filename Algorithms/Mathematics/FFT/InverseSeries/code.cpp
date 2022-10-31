Poly invert(const Poly& x, int s) {
  Poly ret = {pw(x[0], mod - 2)};
  int k = 1;
  for (; k < s; k *= 2) {
    ret = ret + ret - (ret * ret) * range(x, 0, 2 * k);
    ret.resize(2 * k);
  }
  ret.resize(s);
  return ret;
}