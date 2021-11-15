#include <bits/stdc++.h>

using namespace std;

#define D(x) x

typedef long long ll;

// return a^b mod m
ll powmod(ll a, ll b, ll m) {
	ll res = 1;
	while(b > 0)
		if(b & 1) res = (res * a) % m, --b;
		else a = (a * a) % m, b >>= 1;
	return res % m;
}

int euler_phi(int n) {
	int result = n;
	for(int i = 2; i * i <= n; i++) {
		if(n % i == 0) {
			while(n % i == 0) n /= i;
			result -= result / i;
		}
	}
	if(n > 1) result -= result / n;
	return result;
}

// computes gcd(a,b)
ll gcd(ll a, ll b) {
	ll tmp;
	while(b) {
		a %= b;
		tmp = a;
		a = b;
		b = tmp;
	}
	return a;
}

int primitive_root(int m) {
	int phi = euler_phi(m); // m-1 if m prime
	int n = phi;
	vector<int> fact;
	for(int i = 2; i * i <= n; ++i)
		if(n % i == 0) {
			fact.push_back(i);
			while(n % i == 0) n /= i;
		}
	if(n > 1) fact.push_back(n);

	for(int res = 2; res < m; ++res) {
		// skip next line if m is prime
		if(gcd(res, m) != 1) continue;
		bool ok = true;
		for(int f : fact)
			if(powmod(res, phi / f, m) == 1) {
				ok = false; break; }
		if(ok) return res;
	}
	return -1; // no root exists
}


int main() {
	ios_base::sync_with_stdio(false);
	cout << setprecision(12) << fixed;

	int x = 9653618; // 2 * 13^6
	cout << "euler_phi(" << x << "): " << euler_phi(x) << endl;
	cout << "primitive_root(" << x << "): " << primitive_root(x) << endl; // 7

	return 0;
}
