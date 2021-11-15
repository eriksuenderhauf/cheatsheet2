#include <bits/stdc++.h>
using namespace std;

struct eertree {
	string str;
	int cnt = 2, suff = 1;
	vector<int> link, len;
	vector<array<int,26>> go;

	eertree(string& s, int n) : link(n), len(n), go(n), str(s) {
		len[1] = -1, len[2] = 0;
		link[1] = 1, link[2] = 1;
	}

	int walk(int i, int v) {
		for (; str[i-1-len[v]] != str[i]; v = link[v]);
		return v;
	}

	void add(int i) {
		int val = str[i] - 'a';
		int lst = walk(i, suff);
		if (!go[lst][val]) {
			len[++cnt] = len[lst] + 2;
			go[lst][val] = cnt;
			link[cnt] = lst == 1 ? 2 : go[walk(i,link[lst])][val];
		}
		suff = go[lst][val];
	}
};

int main() {
	string s; cin >> s;
	int n = s.size();
	eertree tree(s, n);
	for (int i = 0; i < n; i++)
		tree.add(i);
	cout << tree.cnt-2 << "\n"; // number of distinct palindromic substrings
}