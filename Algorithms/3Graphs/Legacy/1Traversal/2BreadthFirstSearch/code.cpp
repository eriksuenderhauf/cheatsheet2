#define MAXN 100000

int n, m;
bitset<MAXN> v;
vector<int> e[MAXN];

// get the indices of the nodes in breadth first search order
vector<int> bfs(int i) {
  v.reset();
  vector<int> o;
  queue<int> q;
  q.push(i);
  while (!q.empty()) {
    int j = q.front();
    q.pop();
    if (v[j])
      continue;
    v[j] = true;
    o.push_back(j);
    for (int k : e[j])
      q.push(k);
  }
  return o;
}
