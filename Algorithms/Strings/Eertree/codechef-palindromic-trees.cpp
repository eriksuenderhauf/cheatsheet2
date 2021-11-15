#include <bits/stdc++.h>
using namespace std;

struct eertree {
	string str;
	int cnt = 2, suff = 1;
	long long sm = 0;
	vector<int> link, len, depth;
	vector<array<int,26>> go;

	eertree(string& s, int n) : link(n+3), len(n+3), go(n+3), depth(n+3), str(s) {
		len[1] = -1, len[2] = 0;
		link[1] = 1, link[2] = 1;
	}

	int walk(int i, int v) {
		while (i-1-len[v] < 0 || str[i-1-len[v]] != str[i])
			v = link[v];
		return v;
	}

	void add(int i) {
		int val = str[i] - 'a';
		int lst = walk(i, suff);
		if (!go[lst][val]) {
			len[++cnt] = len[lst] + 2;
			go[lst][val] = cnt;
			link[cnt] = lst == 1 ? 2 : go[walk(i,link[lst])][val];
			depth[cnt] = depth[link[cnt]] + 1;
		}
		suff = go[lst][val];
		sm += depth[suff];
	}
};

int main() {
	int T; cin >> T;
	while (T--) {
		string s; cin >> s;
		int n = s.size();
		eertree tree(s, n);
		for (int i = 0; i < n; i++)
			tree.add(i);
		cout << tree.cnt-2 << " " << tree.sm << "\n";
	}
}