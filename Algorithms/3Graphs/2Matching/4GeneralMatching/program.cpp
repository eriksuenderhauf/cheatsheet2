#include <bits/stdc++.h>
#define sz(x) (int)(x).size()
#define pb push_back
#define pii pair<int,int>
#define st first
#define nd second
typedef long long ll;
typedef long double ld;
using namespace std;
const int N = 1e2 + 5;
string str[N];
int n, m, nx[M], par[M];
int mate[N], vis[N], mrk[N];
vector<int> adj[N];
queue<int> pq;

int qry(int x) { return x == par[x] ? x : par[x] = qry(par[x]); }
void join(int x, int y) { par[qry(x)] = qry(y); }

int lca(int x, int y) {
  static int t=0;
  for (t++; ;swap(x,y)) if (x != -1) {
    if (vis[x=qry(x)]==t) return x;
    vis[x] = t;
    x = (mate[x]!=-1)?nx[mate[x]]:-1;
  }
}

void group(int a, int p) {
  for (int b,c; a != p; join(a,b), join(b,c),a=c) {
    b=mate[a], c=nx[b];
    if (qry(c) != p) nx[c] = b;
    if (mrk[b] == 2) mrk[b] = 1, pq.push(b);
    if (mrk[c] == 2) mrk[c] = 1, pq.push(c);
  }
}

void aug(int s) {
  for (int i = 0; i < n; i++)
    nx[i] = vis[i] = -1, par[i] = i, mrk[i] = 0;
  while (!pq.empty()) pq.pop();
  pq.push(s); mrk[s] = 1;
  while (mate[s] == -1 && !pq.empty()) {
    int x = pq.front(); pq.pop();
    for (int i = 0,y; i < sz(adj[x]); i++) {
      if ((y=adj[x][i]) != mate[x] && qry(x)!=qry(y)&&mrk[y]!=2) {
        if (mrk[y]==1) {
          int p = lca(x, y);
          if (qry(x)!=p) nx[x] = y;
          if (qry(y)!=p) nx[y] = x;
          group(x,p); group(y,p);
        } else if (mate[y]==-1) {
          nx[y]=x;
          for (int j=y,k,l; j != -1; j=l) {
            k=nx[j]; l = mate[k];
            mate[j] = k; mate[k] = j;
          }
          break;
        } else {
          nx[y] = x;
          pq.push(mate[y]);
          mrk[mate[y]] = 1;
          mrk[y] = 2;
        }
      }
    }
  }
}

int matching() {
  fill(mate, mate+n+1, -1);
  for (int i = 0; i < n; i++)
    if (mate[i] == -1)
      aug(i);
  int ret = 0;
  for (int i = 0; i < n; i++) {
    ret += mate[i] > i;
  }
  return ret;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout << fixed << setprecision(10);
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int u, v; cin >> u >> v;
    u--, v--;
    adj[u].pb(v); adj[v].pb(u);
  }
  cout << matching() << "\n";
  return 0;
}