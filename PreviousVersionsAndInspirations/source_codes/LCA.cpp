typedef vector<int> VI;
typedef int INFO; // information that is written into the nodes

INFO combine(const INFO &a, const INFO &b){ // combines two infos, e.g. returns min(a,b)
  return min(a,b);
}

// Nodes are numbered 1..n
// After all edges are added with addEdge(), build(root) has to be called
// query(a,b) is used to make query of path a, ..., b
struct LCA_Tree{
  int N;
  vector<VI> adj, p;
  vector<vector<INFO> > p_info;
  vector<INFO> node_info;
  VI depth, log;

  LCA_Tree(int n):N(n), adj(n+1), p(n+1, VI(20)), p_info(n+1, vector<INFO>(20)), node_info(n+1), depth(n+1), log(n+1){
    for(int k=1, l=0; k <= N; k++){
      if((1<<(l+1)) <= k)
	l++;
      log[k] = l;
    }
  }
  
  void set_node_info(int i, INFO info){
    node_info[i] = info;
  }

  void addEdge(int a, int b){
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  void build(int root=1){
    dfs(root, root);
    for(int l=1; l<=log[N]; l++)
      for(int k=1; k<=N; k++){
	p[k][l] = p[ p[k][l-1] ][ l-1 ];
	p_info[k][l] = combine(p_info[k][l-1], p_info[ p[k][l-1] ][l-1]);
      }
  }

  void dfs(int i, int prev, int d=0){
    depth[i] = d;
    p[i][0] = prev;
    p_info[i][0] = node_info[prev];
    for(int c:adj[i])
      if(c!=prev)
	dfs(c, i, d+1);
  }

  INFO query(int a, int b){
    if(depth[a]>depth[b])
      swap(a,b);

    INFO res = node_info[b];

    while(depth[a]!=depth[b]){
      res = combine(res, p_info[b][ log[ depth[b]-depth[a] ] ]);
      b = p[ b ][ log[ depth[b]-depth[a] ] ];
    }

    if(a==b) // a is LCA
      return res;

    res = combine(res, node_info[a]);

    for(int l=log[N]; l>=0; l--)
      if(p[a][l]!=p[b][l]){
	res = combine(res, combine(p_info[a][l], p_info[b][l]));
	a = p[a][l], b = p[b][l];
      }

    return combine(res, p_info[a][0]); // a is LCA
  }
};


int main(){
  LCA_Tree tree(5);
  tree.addEdge(1,2);  tree.addEdge(1,4);   tree.addEdge(3,2);   tree.addEdge(5,2);
  for(int i=1;i<=5;i++)
    tree.set_node_info(i, i);

  tree.build(1);
  cout<<tree.query(2,5)<<endl; // 2
  cout<<tree.query(5,3)<<endl; // 2
  cout<<tree.query(4,3)<<endl; // 1
  cout<<tree.query(3,3)<<endl; // 3
  return 0;
}
