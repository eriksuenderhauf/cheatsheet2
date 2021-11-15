#define MAXN 100005

typedef int DATA; // DP Data
typedef pair<int,int> SDATA; // Sum DP Data

struct EDGE{
  int to;
  int back_idx;
  DATA dp;

  EDGE(int t):to(t),dp(-1){}
};

vector<EDGE> adj[MAXN];
char vis[MAXN];
SDATA sum[MAXN];
EDGE* missing_edge[MAXN];

void add_to_sum(SDATA &s, const DATA &d){
  if(d > s.first){
    swap(s.first, s.second);
    s.first = d;
  }
  else if(d > s.second)
    s.second = d;
}

DATA sub_from_sum(const SDATA &s, const DATA &d){
  return s.first==d ? s.second : s.first;
}

void add_edge(int a, int b){ // adds edge in both directions
  adj[a].push_back(EDGE(b));
  adj[b].push_back(EDGE(a));
  adj[b].back().back_idx = adj[a].size()-1;
  adj[a].back().back_idx = adj[b].size()-1;
}

void dfs(int n, int from, EDGE& from_e){
  if(from_e.dp != -1)
    return;
  if(adj[n].size()==1 && from!=-1){ // leaf
      from_e.dp = 1;
      return;
    }
	
  if(vis[n] >= 1){
    if(missing_edge[n] != NULL){
	  dfs(missing_edge[n]->to, n, *missing_edge[n]);
	  add_to_sum(sum[n], missing_edge[n]->dp);
	  missing_edge[n] = NULL;
	}
    
      if(from==-1)
	from_e.dp = sub_from_sum(sum[n], 0); // subtract sth. neutral
      else
	from_e.dp = sub_from_sum(sum[n], adj[n][from_e.back_idx].dp); 

      from_e.dp++;
      return;
    }

	
  missing_edge[n] = NULL;	
  sum[n] = SDATA(0,0);
  
  for(auto &e:adj[n]){
    if(e.to == from){ 
      missing_edge[n] = &e;
      continue;
    }

    dfs(e.to, n, e);
    add_to_sum(sum[n], e.dp);
  }
	
  from_e.dp = sub_from_sum(sum[n], 0) + 1; // subtract sth. neutral
  vis[n] = 1;
}  

DATA calculate(int n){
  EDGE e(n);
  dfs(n,-1,e);
  return e.dp-1;
}

void init(int n){
  for(int i=0;i<=n;i++){
    adj[i].clear();
    vis[i] = 0;
  }
}

int main(){
  int n;
  cin >> n;

  init(n);
  
  for(int i = 0; i < n - 1; i++){
    int a, b; cin >> a >> b;
    add_edge(a+1,b+1);
  }
  
  int best_ttl=n+1;
  for(int i = 1; i <= n; i++)
    best_ttl = min(best_ttl,calculate(i));

  cout<<(best_ttl)<<endl;
  return 0;
}
