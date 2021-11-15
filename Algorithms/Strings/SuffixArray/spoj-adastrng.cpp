#include <bits/stdc++.h>
#define st first
#define nd second
#define trav(x, a) for (const auto& x: a)
#define sz(x) (int)(x).size()
#define pb push_back
#define pii pair<int,int>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e6 + 5;
int lcp[N], rnk[N], c[N];
int suf[N], sra[N], tsu[N];

void countingSort(int k, int n) {
  int mra = 0, sum = 0, tmp = 0;
  fill(c, c+n+1, 0);
  for (int i = 0; i < n; i++)
    c[i + k < n ? sra[i + k] + 1 : 0]++, mra = max(mra, i + k < n ? sra[i + k] + 1 : 0);
  for (int i = 0; i <= mra; i++)
    tmp = sum + c[i], c[i] = sum, sum = tmp;
  for (int i = 0; i < n; i++)
    tsu[c[suf[i] + k < n ? sra[suf[i] + k] + 1 : 0]++] = suf[i];
  for (int i = 0; i < n; i++)
    suf[i] = tsu[i];
}

void suffixArray(string & s) {
  int n = sz(s);
  for(int i = 0; i < n; i++) {
    suf[i] = i;
    sra[i] = s[i]-'a';
  }
  for(int k = 1; k < n; k <<= 1) {
    countingSort(k, n);
    countingSort(0, n);
    tsu[suf[0]] = 0;
    for(int i = 1; i < n; i++)
      tsu[suf[i]] = tsu[suf[i - 1]] + ((sra[suf[i]] == sra[suf[i - 1]] && (suf[i] + k < n ? sra[suf[i] + k] : -1) == (suf[i - 1] + k < n ? sra[suf[i - 1] + k] : -1)) ? 0 : 1);
    for(int i = 0; i < n; i++)
      sra[i] = tsu[i];
    if(sra[suf[n - 1]] == n - 1)
      break;
  }
}

ll ans[30];

void solve() {
  string a; cin >> a;
  int m = sz(a);
  suffixArray(a);
  for (int i = 0; i < m; i++)
    rnk[suf[i]] = i;
  for (int i = 0, k = 0; i < m; i++) {
    if (rnk[i] == m - 1) {
      k = 0;
      continue;
    }
    int j = suf[rnk[i] + 1];
    while (max(i, j) + k < m && a[i+k] == a[j+k])
      k++;
    lcp[rnk[i]] = k;
    if (k) k--;
  }
  for (int i = 0; i < m; i++) {
    ans[a[suf[i]]-'a'] += m - suf[i];
    if (i > 0)
      ans[a[suf[i]]-'a'] -= lcp[i-1];
  }
  for (int i = 0; i < 26; i++)
    cout << ans[i] << " \n"[i == 25];
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int t = 1; // cin >> t;
  while (t--)
    solve();
}