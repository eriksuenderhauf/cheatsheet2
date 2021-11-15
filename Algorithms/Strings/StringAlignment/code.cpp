int n, m, ins, del, cha, mat, c[1000][1000];
string a, b;

int main() {
	cin >> a >> b;
	n = a.size(), m = b.size();
	// scores for inserting, deleting, changing and keeping a character (0, 0, -inf, 1 for longest common substring)
	cin >> ins >> del >> cha >> mat;

	for(int i = 0; i <= n; i++)
		c[i][0] = i * del;
	for(int i = 0; i <= m; i++)
		c[0][i] = i * ins;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			c[i][j] = max(max(c[i - 1][j] + del, c[i][j - 1] + ins), c[i - 1][j - 1] + (a[i] == b[j] ? mat : cha));

	// the costs of aligning the strings
	c[n][m];
}
