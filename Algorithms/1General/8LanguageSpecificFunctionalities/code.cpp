// integer logarithm for positive int (rounded down)
#define log2(x) (31 - __builtin_clz(x))
// integer logarithm for positive long long (rounded down)
#define log2ll(x) (63 - __builtin_clzll(x))

//overflow checking
int a,b,c;
if (__builtin_saddll_overflow(a,b,&c))
	printf("a + b > INT_MAX");
else
	printf("%d + %d = %d",a,b,c);
long long d,e,f;
if (__builtin_smulll_overflow(d,e,&f))
	printf("a * b > LONG_LONG_MAX");
else
	printf("%lld * %lld = %lld",d,e,f);
// similar functions exist for subtraction
// and various data types (s = signed, u = unsigned
// e.g. __builtin_usubll_overflow for unsigned long long

// min/max values of data types, e.g:
numeric_limits<double>()::max();
numeric_limits<int>()::min();

//Hash map with the same API as unordered_map, but ~3x faster. Initial capacity must be a power of 2 (if provided).
#include <bits/extc++.h>
__gnu_pbds::gp_hash_table<ll, int> h({},{},{},{}, {1 << 16});

//sets int x to the larger number with the same number of bits set
int c = x&-x, r = x+c;
x = (((r^x) >> 2)/c) | r;
