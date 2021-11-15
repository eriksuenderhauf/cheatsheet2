double nearestPairOfPoints(vector<point>& a) {
	int n = a.size(), l = 0;
	set<point> cur;
	double ans = 1e18;
	sort(a.begin(), a.end());
	for (int i = 0; i < n; i++) {
		while (a[l].x < a[i].x && (a[l].x - a[i].x) * (a[l].x - a[i].x) > ans)
			cur.erase(a[l++]);
		auto lo = cur.lower_bound({a[i].x - sqrt(ans) - eps, a[i].y});
		auto hi = cur.upper_bound({a[i].x + sqrt(ans) + eps, a[i].y});
		while (lo != hi) {
			ans = min(ans, dist(*lo, a[i]) * dist(*lo, a[i]));
			lo = next(lo);
		}
	}
	return ans;
}