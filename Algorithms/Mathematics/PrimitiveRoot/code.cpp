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
