#include <bits/stdc++.h>
#define sz(x) (int)(x).size()
using namespace std;

#define log2(x) (31 - __builtin_clz(x))

struct sparse_table {
  int n;
  vector<int> a;
  vector<vector<int>> st;
  int combine(int dl, int dr) {
    return a[dl] < a[dr] ? dl : dr;
  }
  sparse_table() {}
  sparse_table(vector<int> & a) : n(a.size()), a(a), st(log2(n) + 1, vector<int>(n)) {
    for (int i = 0; i < n; i++)
      st[0][i] = i;
    for (int j = 1; 1 << j <= n; j++)
      for (int i = 0; i + (1 << j) <= n; i++)
        st[j][i] = combine(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
  }
  // query the data on the range [l, r[
  int query(int l, int r) {
    int s = log2(r - l);
    return combine(st[s][l], st[s][r - (1 << s)]);
  }
};

struct suffix_array {
  int n;
  vector<int> rnk, c, suf, sra, tsu, lcp;
  sparse_table sp;
  string s;
  suffix_array() {}
  suffix_array(string& s) : s(s), n(sz(s)), rnk(n+1), c(26*n+1), suf(n+1), sra(n+1), tsu(n+1), lcp(n+1) {
    for(int i = 0; i < n; i++)
      suf[i] = i, sra[i] = s[i]-'a';
    for(int k = 1; k < n; k <<= 1) {
      countingSort(k);
      countingSort(0);
      tsu[suf[0]] = 0;
      for(int i = 1; i < n; i++)
        tsu[suf[i]] = tsu[suf[i - 1]] + ((sra[suf[i]] == sra[suf[i - 1]] && (suf[i] + k < n ? sra[suf[i] + k] : -1) == (suf[i - 1] + k < n ? sra[suf[i - 1] + k] : -1)) ? 0 : 1);
      for(int i = 0; i < n; i++)
        sra[i] = tsu[i];
      if(sra[suf[n - 1]] == n - 1)
        break;
    }
  }
  void countingSort(int k) {
    int mra = 0, sum = 0, tmp = 0;
    fill(c.begin(), c.end(), 0);
    for (int i = 0; i < n; i++)
      c[i + k < n ? sra[i + k] + 1 : 0]++, mra = max(mra, i + k < n ? sra[i + k] + 1 : 0);
    for (int i = 0; i <= mra; i++)
      tmp = sum + c[i], c[i] = sum, sum = tmp;
    for (int i = 0; i < n; i++)
      tsu[c[suf[i] + k < n ? sra[suf[i] + k] + 1 : 0]++] = suf[i];
    for (int i = 0; i < n; i++)
      suf[i] = tsu[i];
  }
  int findString(const string & p, bool eql) {
    int l = 0, r = n - 1;
    while(l < r) {
      int m = (l + r) / 2;
      int res = strncmp(& s.front() + suf[m], & p.front(), p.size());
      if(res > 0 || (eql && res == 0))
        r = m;
      else
        l = m + 1;
    }
    int res = strncmp(& s.front() + suf[l], & p.front(), p.size());
    if(res < 0 || (!eql && res == 0))
      l++;
    return l;
  }
  // get the indices of matches from p in s
  vector<int> findMatches(const string & p) {
    int l = findString(p, true), r = findString(p, false);
    vector<int> res;
    for(int i = l; i < r; i++)
      res.push_back(suf[i]);
    return res;
  }
  // initialize the longest common prefix, get the starting index and the length of the longest repeated substring
  pair<int, int> longestCommonPrefix() {
    int lrs = 0, rsp = -1;
    for (int i = 0; i < n; i++)
      rnk[suf[i]] = i;
    for (int i = 0, k = 0; i < n; i++) {
      if (rnk[i] == n - 1) {
        k = 0;
        continue;
      }
      int j = suf[rnk[i] + 1];
      while (max(i, j) + k < n && s[i + k] == s[j + k])
        k++;
      lcp[rnk[i]] = k;
      if (k > lrs)
        lrs = k, rsp = i;
      k = max(k - 1, 0);
    }
    sp = sparse_table(lcp);
    return {rsp, lrs};
  }
  // get the length of the longest common prefix starting at i and j
  int getLongestCommonPrefix(int i, int j) {
    if (i == j)
      return n - i;
    i = rnk[i]; j = rnk[j];
    if (i > j)
      swap(i, j);
    return lcp[sp.query(i, j)];
  }
  // get the length of the longest common suffix ending at i and j
  int getLongestCommonSuffix(int i, int j) {
    int l = 1, r = min(i, j) + 1;
    while (l <= r) {
      int m = (l + r) / 2;
      if (getLongestCommonPrefix(i - m + 1, j - m + 1) >= m)
        l = m + 1;
      else
        r = m - 1;
    }
    return r;
  }
  int operator[](int i) {
    return suf[i];
  }
};

int main() {
  string s; cin >> s;
  suffix_array sa(s);
  sa.longestCommonPrefix();
  cout << sa.getLongestCommonSuffix(3, 0) << endl;
  cout << sa.getLongestCommonSuffix(3, 1) << endl;
  cout << sa.getLongestCommonSuffix(3, 2) << endl;
}