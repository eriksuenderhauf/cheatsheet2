// Primes less than 1000:
//     2    3    5    7   11   13   17   19   23   29   31   37
//    41   43   47   53   59   61   67   71   73   79   83   89
//    97  101  103  107  109  113  127  131  137  139  149  151
//   157  163  167  173  179  181  191  193  197  199  211  223
//   227  229  233  239  241  251  257  263  269  271  277  281
//   283  293  307  311  313  317  331  337  347  349  353  359
//   367  373  379  383  389  397  401  409  419  421  431  433
//   439  443  449  457  461  463  467  479  487  491  499  503
//   509  521  523  541  547  557  563  569  571  577  587  593
//   599  601  607  613  617  619  631  641  643  647  653  659
//   661  673  677  683  691  701  709  719  727  733  739  743
//   751  757  761  769  773  787  797  809  811  821  823  827
//   829  839  853  857  859  863  877  881  883  887  907  911
//   919  929  937  941  947  953  967  971  977  983  991  997

// Other primes:
//    The largest prime smaller than 10 is 7.
//    The largest prime smaller than 10^2 is 97.
//    The largest prime smaller than 10^3 is 997.
//    The largest prime smaller than 10^4 is 9973.
//    The largest prime smaller than 10^5 is 99991.
//    The largest prime smaller than 10^6 is 999983.
//    The largest prime smaller than 10^7 is 9999991.
//    The largest prime smaller than 10^8 is 99999989.
//    The largest prime smaller than 10^9 is 999999937.
//    The largest prime smaller than 10^10 is 9999999967.
//    The largest prime smaller than 10^11 is 99999999977.
//    The largest prime smaller than 10^12 is 999999999989.
//    The largest prime smaller than 10^13 is 9999999999971.
//    The largest prime smaller than 10^14 is 99999999999973.
//    The largest prime smaller than 10^15 is 999999999999989.
//    The largest prime smaller than 10^16 is 9999999999999937.
//    The largest prime smaller than 10^17 is 99999999999999997.
//    The largest prime smaller than 10^18 is 999999999999999989.
//    (1<<61)-1 is prime

// This is a collection of useful code for solving problems that
// involve modular linear equations.  Note that all of the
// algorithms described here work on nonnegative integers.

typedef vector<int> VI;
typedef pair<int,int> PII;

// return a % b (positive value)
int mod(int a, int b) {
  return ((a%b)+b)%b;
}

// computes gcd(a,b)
int gcd(int a, int b) {
  int tmp;
  while(b){a%=b; tmp=a; a=b; b=tmp;}
  return a;
}

// computes lcm(a,b)
int lcm(int a, int b) {
  return a/gcd(a,b)*b;
}

// returns d = gcd(a,b); finds x,y such that d = ax + by
int extended_euclid(int a, int b, int &x, int &y) {  
  int xx = y = 0;
  int yy = x = 1;
  while (b) {
    int q = a/b;
    int t = b; b = a%b; a = t;
    t = xx; xx = x-q*xx; x = t;
    t = yy; yy = y-q*yy; y = t;
  }
  return a;
}

// finds all solutions to ax = b (mod n)
VI modular_linear_equation_solver(int a, int b, int n) {
  int x, y;
  VI solutions;
  int d = extended_euclid(a, n, x, y);
  if (!(b%d)) {
    x = mod (x*(b/d), n);
    for (int i = 0; i < d; i++)
      solutions.push_back(mod(x + i*(n/d), n));
  }
  return solutions;
}

// computes b such that ab = 1 (mod n), returns -1 on failure
int mod_inverse(int a, int n) {
  int x, y;
  int d = extended_euclid(a, n, x, y);
  if (d > 1) return -1;
  return mod(x,n);
}

// Chinese remainder theorem (special case): find z such that
// z % x = a, z % y = b.  Here, z is unique modulo M = lcm(x,y).
// Return (z,M).  On failure, M = -1.
PII chinese_remainder_theorem(int x, int a, int y, int b) {
  int s, t;
  int d = extended_euclid(x, y, s, t);
  if (a%d != b%d) return make_pair(0, -1);
  return make_pair(mod(s*b*x+t*a*y,x*y)/d, x*y/d);
}

// Chinese remainder theorem: find z such that
// z % x[i] = a[i] for all i.  Note that the solution is
// unique modulo M = lcm_i (x[i]).  Return (z,M).  On 
// failure, M = -1.  Note that we do not require the a[i]'s
// to be relatively prime.
PII chinese_remainder_theorem(const VI &x, const VI &a) {
  PII ret = make_pair(a[0], x[0]);
  for (int i = 1; i < x.size(); i++) {
    ret = chinese_remainder_theorem(ret.second, ret.first, x[i], a[i]);
    if (ret.second == -1) break;
  }
  return ret;
}

// computes x and y such that ax + by = c; on failure, x = y =-1
void linear_diophantine(int a, int b, int c, int &x, int &y) {
  int d = gcd(a,b);
  if (c%d) {
    x = y = -1;
  } else {
    x = c/d * mod_inverse(a/d, b/d);
    y = (c-a*x)/b;
  }
}

int main() {
  
  // expected: 2
  cout << gcd(14, 30) << endl;
  
  // expected: 2 -2 1
  int x, y;
  int d = extended_euclid(14, 30, x, y);
  cout << d << " " << x << " " << y << endl;
  
  // expected: 95 45
  VI sols = modular_linear_equation_solver(14, 30, 100);
  for (int i = 0; i < (int) sols.size(); i++) cout << sols[i] << " "; 
  cout << endl;
  
  // expected: 8
  cout << mod_inverse(8, 9) << endl;
  
  // expected: 23 56
  //           11 12
  int xs[] = {3, 5, 7, 4, 6};
  int as[] = {2, 3, 2, 3, 5};
  PII ret = chinese_remainder_theorem(VI (xs, xs+3), VI(as, as+3));
  cout << ret.first << " " << ret.second << endl;
  ret = chinese_remainder_theorem (VI(xs+3, xs+5), VI(as+3, as+5));
  cout << ret.first << " " << ret.second << endl;
  
  // expected: 5 -15
  linear_diophantine(7, 2, 5, x, y);
  cout << x << " " << y << endl;

}
