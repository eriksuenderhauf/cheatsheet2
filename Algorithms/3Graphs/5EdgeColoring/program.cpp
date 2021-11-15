#include <bits/stdc++.h>

using namespace std;

// Implementation of the Misra-Gries algorithm to find a near-optimal edge-coloring in O(V*E).
// Given a graph maximum degree D, an optimal edge-coloring takes either
// D or D + 1 colors. This algorithm returns a (D + 1)-coloring.
// In practice, it can color a complete graph with 2000 vertices in roughly 1 second.

// Initialisation: provide the number of vertices n and the expected maximum degree D
// add_edge(u, v) for 0 <= u, v < n adds the corresponding edge to the coloring
// afterwards, color[u][v] gives the color of edge (u, v) from the range [0, D]

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

void test() {
	int n = 2000;
	edge_coloring g(n, n - 1);
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < i; ++j) {
			g.add_edge(i, j);
		}
	}

	cout << "computation complete!" << endl;

	vector <vector <int > > x(n, vector <int > (n, 0));

	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < i; ++j) {
			if(x[i][g.color[i][j]] > 0 || x[j][g.color[i][j]] > 0) {
				cout << "faulty!" << endl;
			}
			++x[i][g.color[i][j]];
			++x[j][g.color[i][j]];
		}
	}
	cout << "verification complete!" << endl;
}

void solve() {
	// Solves task 'Game Scheduling' from NCPC 2018
	int n, m;
	cin >> n >> m;
	edge_coloring g(n * m, n * (m - 1));

	for(int t0 = 0; t0 < m; ++t0) {
		for(int p0 = 0; p0 < n; ++p0) {
			for(int t1 = 0; t1 < t0; ++t1) {
				for(int p1 = 0; p1 < n; ++p1) {
					g.add_edge(t0 * n + p0, t1 * n + p1);
				}
			}
		}
	}
	vector <stringstream> rounds(n * (m - 1) + 1);

	for(int t0 = 0; t0 < m; ++t0) {
		for(int p0 = 0; p0 < n; ++p0) {
			for(int t1 = 0; t1 < t0; ++t1) {
				for(int p1 = 0; p1 < n; ++p1) {
					rounds[g.color[t0 * n + p0][t1 * n + p1]] << (char)('A' + t0) << p0 + 1 << "-" << (char)('A' + t1) << p1 + 1 << " ";
				}
			}
		}
	}

	for(int i = 0; i < n * (m - 1) + 1; ++i) {
		cout  << rounds[i].str() << endl;
	}
}

int main() {
	test();
	return 0;
}
