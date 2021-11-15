#define MAXN 1000

int n, m, mat[MAXN], lev[MAXN];
bool ibg;
bitset<MAXN> v;
vector<int> vl, e[MAXN];

bool findPath(int i) {
	for (int j : e[i]) {
		if (v[j])
			continue;
		v[j] = true;
		if (mat[j] == -1 || findPath(mat[j])) {
			mat[i] = j; mat[j] = i;
			return true;
		}
	}
	return false;
}

void dfs(int i, int l = 1) {
	lev[i] = l;
	if (l == 1)
		vl.push_back(i);
	for (int j : e[i])
		if (!lev[j])
			dfs(j, 3 - l);
	else
		ibg = ibg && lev[i] != lev[j];
}

// get the size of the matching and the indices of the matched vertices
pair<int, vector<pair<int, int>>> maxCardinalityBipartiteMatching() {
	int mbm = 0, prev = 0;
	ibg = true;
	vl.clear();
	for (int i = 0; i < n; i++)
		mat[i] = -1, lev[i] = 0;
	for (int i = 0; i < n; i++)
		if (!lev[i])
			dfs(i);
	if (!ibg)
		return {-1, vector<pair<int, int>>()};
	do {
		prev = mbm;
		v.reset();
		for (int i : vl)
			if (mat[i] == -1)
				mbm += findPath(i);
	} while (mbm > prev);
	vector<pair<int, int>> ma;
	for (int i : vl)
		if (mat[i] != -1)
			ma.push_back({i, mat[i]});
	return {mbm, ma};
}

//code below constructs min vertex cover using koenigs theorem
void cover_dfs(int i)
{
	v[i]=true;
	for (int g : e[i])
		if (!v[g] && lev[i]-1 == (mat[i] == g))		
			cover_dfs(g);
}
vector<int> min_vertex_cover()
{
	maxCardinalityBipartiteMatching();
	v.reset();
	for (int i=0; i<n; i++)
		if (lev[i] == 1 && mat[i] == -1)
			cover_dfs(i);
	vector<int> cover;
	for (int i=0; i<n; i++)
		if (lev[i]-1 == v[i])
			cover.push_back(i);
	return cover;
}
