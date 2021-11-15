typedef vector<int> VI;
typedef vector<vector<int>> VVI;

struct edge_coloring {
	VVI color, adj, free; VI y, t;

	edge_coloring(int n, int D) : color(n, VI(n, -1)), adj(n, VI(D + 1, -1)), free(n, VI(D + 1)), y(n), t(D + 1) {
		for(int i = 0; i < n; ++i)
			for(int j = 0; j <= D; ++j)
				free[i][j] = D - j;
	}

	int find_common(int u, int v) {
		while(adj[v][free[v].back()] != -1)
			free[v].pop_back();
		if(adj[v][free[u].back()] == -1)
			return free[u].back();
		if(adj[u][free[v].back()] == -1)
			return free[v].back();
		return -1;
	}

	int   trace(int a, int b, int q, int r) {
		int s = adj[r][b];
		color[q][r] = color[r][q] = b;
		adj[q][b] = r; adj[r][b] = q;
		if(s != -1) return trace(b, a, r, s);
		adj[r][a] = -1;
		free[r].push_back(a);
		return r;
	}

	void add_edge(int u, int v) {
		while(adj[u][free[u].back()] != -1)
			free[u].pop_back();

		y[0] = v;
		int j = 0, c = find_common(u, v);

		while(c < 0) {
			c = free[y[j]].back();
			if(t[c] < j && free[y[t[c]]].back() == c) {
				if(trace(c, free[u].back(), u, adj[u][c]) != y[t[c]]) j = t[c];
				break;
			}
			t[c] = j++; y[j] = adj[u][c];
			c = find_common(u, y[j]);
		}

		while(j >= 0) {
			int v = y[j], d = color[u][v];
			adj[u][c] = v; adj[v][c] = u;
			if(j > 0) {
				free[u].push_back(d);
				free[v].push_back(d);
				adj[u][d] = adj[v][d] = -1;
			}
			color[u][v] = color[v][u] = c;
			c = d; --j;
		}
	}
};
