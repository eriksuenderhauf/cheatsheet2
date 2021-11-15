int dlog(int a, int b, int m) {
	int n = sqrt((double)m) + 1;
	map<int, int> vals;
	for(int i = n; i >= 1; --i)
		vals[powmod(a, i * n, m)] = i;
	for(int i = 0; i <= n; ++i) {
		int cur = (powmod(a, i, m) * b) % m;
		if(vals.count(cur)) {
			int ans = vals[cur] * n - i;
			if(ans < m) return ans;
		}
	}
	return -1;
}
