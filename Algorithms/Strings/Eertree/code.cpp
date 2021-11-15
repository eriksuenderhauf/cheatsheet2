struct eertree {
	string str;
	int cnt = 2, suf = 1;
	vector<int> lnk, len, dif, slnk;
	vector<array<int,26>> go;
	eertree(string& s, int n) : lnk(n+3), len(n+3), go(n+3), dif(n+3), slnk(n+3), str(s) {
		len[1] = -1, len[2] = 0;
		lnk[1] = 1, lnk[2] = 1;
	}
	int walk(int i, int v) {
		while (i-1-len[v] < 0 || str[i-1-len[v]] != str[i])
			v = lnk[v];
		return v;
	}
	void add(int i) {
		int c = str[i]-'a', lst = walk(i, suf);
		if (!go[lst][c]) {
			go[lst][c] = ++cnt;
			len[cnt] = len[lst] + 2;
			lnk[cnt] = lst > 1 ? go[walk(i,lnk[lst])][c] : 2;
			dif[cnt] = len[cnt] - len[lnk[cnt]];
			slnk[cnt] = dif[cnt] == dif[lnk[cnt]] ? slnk[lnk[cnt]] : lnk[cnt];
		}
		suf = go[lst][c];
	}
};