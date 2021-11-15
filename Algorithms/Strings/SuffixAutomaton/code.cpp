struct SA {
	struct state {
		int len, link;
		map<char, int> next;
	};
	vector<state> st;
	int last = 0;

	SA() { st.push_back({0, -1}); }
	SA(string &s) : SA() {
		st.reserve(2*s.size());
		for (char c : s) append(c);
	}
	void append(char c) {
		int cur = st.size(), p = last;
		st.push_back({st[last].len + 1, 0});
		for (; p != -1 && !st[p].next.count(c); p = st[p].link)
			st[p].next[c] = cur;
		if (p != -1) {
			int q = st[p].next[c];
			if (st[p].len + 1 == st[q].len)
				st[cur].link = q;
			else {
				int clone = st.size();
				st.push_back({st[p].len + 1, st[q].link, st[q].next});
				st[q].link = st[cur].link = clone;
				for (; p != -1 && st[p].next[c] == q; p = st[p].link)
					st[p].next[c] = clone;
			}
		}
		last = cur;
	}
	bool contains(string &t) {
		int p = 0;
		for (char c : t) {
			if (!st[p].next.count(c))
				return false;
			p = st[p].next[c];
		}
		return true;
	}
};
string lcs(string &S, string &T) { //longest common substring
	SA s(S);
    int v = 0, l = 0, best = 0, bestpos = 0;
	for (size_t i = 0; i < T.size(); i++) {
		while (v && !s.st[v].next.count(T[i])) {
			v = s.st[v].link;
			l = s.st[v].len;
		}
		if (s.st[v].next.count(T[i]))
			v = s.st[v].next[T[i]], l++;
		if (l > best)
			best = l, bestpos = i;
	}
	return T.substr(bestpos - best + 1, best);
}
