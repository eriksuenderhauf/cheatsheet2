int __builtin_clz (unsigned int x);
// Returns the number of leading 0-bits in x, starting at the most significant bit position. If x is 0, the result is undefined.

int __builtin_ctz (unsigned int x)
// Returns the number of trailing 0-bits in x, starting at the least significant bit position. If x is 0, the result is undefined.

int __builtin_popcount (unsigned int x)
// Returns the number of 1-bits in x.

int __builtin_ffs (int x)
// Returns one plus the index of the least significant 1-bit of x, or if x is zero, returns zero.

// For long long arguments add ll to the function name, e.g. __builtin_clzll(long long x)
