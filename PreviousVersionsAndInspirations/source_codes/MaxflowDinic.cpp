#defineNN 105 // the maximum number of vertices
int cap[NN][NN], deg[NN], adj[NN][NN]; //cap[u][v] is the capacity of the edge u->v
int q[NN], prev[NN]; // BFS stuff
int dinic( int n, int s, int t ) {
  int flow = 0;
  while( true ){ // find an augmenting path
    memset( prev, -1, sizeof( prev ) );
  int qf = 0, qb = 0;  prev[q[qb++] = s] = -2;
  while( qb > qf && prev[t] == -1 )
    for( int u = q[qf++], i = 0, v; i < deg[u]; i++ )
      if( prev[v = adj[u][i]] == -1 && cap[u][v] )
        prev[q[qb++] = v] = u;
  if( prev[t] == -1 ) break; // we're done finding paths
    for( int z = 0; z <n; z++ )
      if( cap[z][t] && prev[z] != -1 ){
        int bot = cap[z][t];
        for( int v = z,u = prev[v]; u >= 0;v = u,u = prev[v] )
          bot = min(bot,cap[u][v]);
        if( !bot ) continue;
          cap[z][t] -= bot; cap[t][z] += bot;
        for( int v =z,u = prev[v]; u >= 0;v = u, u =prev[v] )
          cap[u][v] -= bot; cap[v][u] += bot;
        flow += bot;
      }
  }
  return flow;
}

int main() {
  memset( cap, 0, sizeof( cap ) );
  int n, s, t, m;
  scanf( " %d %d %d %d", &n, &s, &t, &m );
  while( m-- ) {
    int u, v, c; scanf( " %d %d %d", &u, &v, &c );
    cap[u][v] = c;
  }
  memset( deg, 0, sizeof( deg ) );
  for( int u = 0; u < n; u++ )
    for( int v = 0; v < n; v++ )
      if( cap[u][v] || cap[v][u] ) adj[u][deg[u]++] = v;
  printf( "%d\n", dinic( n, s, t ) );
}
