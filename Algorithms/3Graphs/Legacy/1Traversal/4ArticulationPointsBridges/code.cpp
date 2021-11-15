#define MAXN 100000

int n, m, cou, num[MAXN], low[MAXN];
bitset<MAXN> v;
vector<int> art, e[MAXN];
vector<pair<int, int>> bri;

//uncomment to assign numbers to double connected components
//stack<int> s; int comp_no, comp[MAXN];

void dfs(int i, int p = -1) {
  v[i] = true; num[i] = low[i] = cou++;
  bool root = p == -1;
  int sub = 0, high = 0;
//s.push(i);
  for (int j : e[i]) {
    if (j == p) {
      p = -1;
      continue;
    }
    if (v[j])
      low[i] = min(low[i], num[j]);
    else {
      dfs(j, i);
      if (low[j] > num[i]) {
        bri.push_back({i, j});
    	/*for (; s.top() != j; s.pop())
    		  comp[s.top()]=comp_no;
    		comp[j]=comp_no++;
    		s.pop(); */
  	  }
      low[i] = min(low[i], low[j]);
      high = max(high, low[j]);
      sub++;
    }
  }
  if (!root && high >= num[i] || root && sub > 1)
    art.push_back(i);
}

// get the indices of the articulation points and the bridges
void articulationPointsBridges() {
  v.reset(); art.clear(); bri.clear(); cou = 0;
  //comp_no = 0;
  for (int i = 0; i < n; i++)
    if (!v[i])
      dfs(i);
/*for (; !s.empty(); s.pop())
    comp[s.top()]=comp_no;
	comp_no++; */
}
