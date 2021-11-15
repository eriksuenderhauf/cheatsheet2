#define MAXN 1000000

int n, m, r[MAXN];
string s;

void preprocessPattern(string & p) {
	r[0] = -1;
	for (int i = 0, j = -1; i < m; i++) {
		while (j >= 0 && p[i] != p[j])
			j = r[j];
		r[i + 1] = ++j;
	}
}

// get the indices of matches from p in s
vector<int> findMatches(string & s, string & p) {
	n = s.size(); m = p.size();
	preprocessPattern(p);
	vector<int> res;
	for (int i = 0, j = 0; i < n; i++) {
		while (j >= 0 && s[i] != p[j])
			j = r[j];
		j++;
		if (j == m)
			res.push_back(i - j + 1), j = r[j];
	}
	return res;
}
