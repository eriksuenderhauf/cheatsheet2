struct Blossom {
  int n, ret; 
  vector<int> mate, par;
  vector<int> nx, dsu, mrk, vis;
  queue<int> pq;
  vector<vector<int>> adj;
  Blossom() {}
  Blossom(int n) : n(n), par(n+5), nx(n+5), mate(n+5), dsu(n+5), mrk(n+5), vis(n+5), adj(n+2) {
    iota(par.begin(), par.end(), 0);
  }

  void add_edge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
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
    for (int i = 0; i <= n; i++)
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
    fill(mate.begin(), mate.end(), -1);
    for (int i = 1; i <= n; i++)
      if (mate[i] == -1)
        aug(i);
    int ret = 0;
    for (int i = 1; i <= n; i++) {
      ret += mate[i] > i;
    }
    return ret;
  }
};