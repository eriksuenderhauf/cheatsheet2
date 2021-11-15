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
const int M = 2*N*N;
string str[N];
int n, m, cnt = 0, nx[M], par[M];
int ar[N][N], mate[M], vis[M], mrk[M];
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
vector<int> adj[M];
queue<int> pq;

bool ok(int x, int y) {
  return 0 <= x && x < n && 0 <= y && y < m;
}

void add(int u, int v) {
  // cout << u << " <-> " << v << "\n";
  adj[u].pb(v);
  adj[v].pb(u);
}

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
  for (int i = 0; i < cnt; i++)
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
  fill(mate, mate+cnt+1, -1);
  for (int i = 0; i < cnt; i++)
    if (mate[i] == -1)
      aug(i);
  int ret = 0;
  for (int i = 0; i < cnt; i++) {
    ret += mate[i] > i;
  }
  return ret;
}

void chk(pii st, set<int>& mex) {
  for (int k = 0; k < 4; k++) {
    int ni = st.st + dx[k], nj = st.nd + dy[k];
    if (ok(ni,nj) && 'a' <= str[ni][nj] && str[ni][nj] <= 'z')
      mex.insert(str[ni][nj]-'a');
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout << fixed << setprecision(10);
  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    cin >> str[i];
    for (int j = 0; j < m; j++) {
      if (str[i][j] == '.')
        ar[i][j] = cnt;
      else
        ar[i][j] = cnt++;
      cnt++;
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (str[i][j] == '+') {
        for (int k = 0; k < 4; k++) {
          int ni = i + dx[k], nj = j + dy[k];
          if (ok(ni,nj) && str[ni][nj] == '.')
            add(ar[i][j], ar[ni][nj]), add(ar[i][j]+1, ar[ni][nj]);
        }
        add(ar[i][j], ar[i][j]+1);
      } else if (str[i][j] == '*') {
        for (int k = 0; k < 4; k++) {
          int ni = i + dx[k], nj = j + dy[k];
          if (ok(ni,nj) && str[ni][nj] == '.')
            add(ar[i][j]+(k&1), ar[ni][nj]);
        }
        add(ar[i][j], ar[i][j]+1);
      }
    }
  }
  matching();
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (str[i][j] != '*' && str[i][j] != '+')
        continue;
      if (mate[ar[i][j]] == -1 || mate[ar[i][j]+1] == -1)
        continue;
      vector<pii> tmp = {{i, j}};
      for (int k = 0; k < 4; k++) {
        int ni = i+dx[k], nj = j+dy[k];
        if (ok(ni,nj) && ar[ni][nj] == mate[ar[i][j]+1])
          tmp.pb({ni, nj});
        else if (ok(ni,nj) && ar[ni][nj] == mate[ar[i][j]])
          tmp.pb({ni, nj});
      }
      if (sz(tmp) != 3) continue;
      set<int> mex;
      for (auto it: tmp) chk(it, mex);
      int mx = 0; while (mex.count(mx)) mx++;
      for (auto it: tmp) str[it.st][it.nd] = (char)(mx+'a');
    }
  }
  for (int i = 0; i < n; i++)
    cout << str[i] << "\n";
  return 0;
}