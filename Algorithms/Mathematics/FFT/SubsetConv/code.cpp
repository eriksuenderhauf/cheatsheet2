#define add(x, y) x = (x + y < mod ? x + y : x + y - mod)
const int N = 1 << 20;
int a[N], b[N], btc[N], ca[N][21], cb[N][21], cc[N][21];
// result is stored in cc[i][btc[i]]
void mul(int n) {
  for (int i = 0; i < 1 << n; i++)
    btc[i] = btc[i / 2] + (i & 1), ca[i][btc[i]] = a[i], cb[i][btc[i]] = b[i];
  for (int i = 2; i <= 1 << n; i *= 2)
    for (int j = 0; j < 1 << n; j += i)
      for (int k = j; k < j+i/2; k++)
        for (int bt = 0; bt <= n; bt++)
          add(ca[k+i/2][bt], ca[k][bt]),
          add(cb[k+i/2][bt], cb[k][bt]);
  for (int msk = 0; msk < 1 << n; msk++)
    for (int i = 0; i <= n; i++) {
      unsigned long long v = 0;
      for (int j = 0; j <= i; j++)
        v += ca[msk][j] * (unsigned long long) cb[msk][i - j];
      cc[msk][i] = v % mod;
    }
  for (int i = 2; i <= 1 << n; i *= 2)
    for (int j = 0; j < 1 << n; j += i)
      for (int k = j; k < j+i/2; k++)
        for (int bt = 0; bt <= n; bt++)
          add(cc[k+i/2][bt], mod-cc[k][bt]);
}