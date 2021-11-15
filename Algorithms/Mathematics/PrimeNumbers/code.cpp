int n, phi[N], lp[N], mu[N];
vector<int> p;
//x = [0].first^[0].second * ...
vector<pair<int, int>> factorise(int x) {
	vector<pair<int, int>> d;
	int y = lp[x], a = 1;
	x /= lp[x];
	while (x > 1) {
		if (lp[x] != y) {
			d.push_back({y, a});
			y = lp[x]; a = 0;
		}
		x /= lp[x], a++;
	}
	d.push_back({y, a});
	return d;
}
void sieve(int n) {
	phi[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (lp[i] == 0) {
			lp[i] = i; phi[i] = i - 1;
			p.push_back(i);
		} else if (lp[i] == lp[i / lp[i]])
			phi[i] = phi[i / lp[i]] * lp[i];
		else
			phi[i] = phi[i / lp[i]] * (lp[i] - 1);
		for (int j = 0; j < (int) p.size() && p[j] <= lp[i] && i * p[j] <= n; j++)
			lp[i * p[j]] = p[j];
	}
}
void moebius(int n) {
  mu[1] = -1;
  for (int i = 1; i <= n; i++) {
    mu[i] *= -1;
    for (int j = 2*i; j <= n; j += i)
      mu[j] += mu[i];
  }
}