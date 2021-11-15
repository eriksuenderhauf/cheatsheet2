#define MAXN 1000000

int n, p[2 * MAXN + 1];

// get the starting index and the length of the longest palindrome
pair<int, int> LongestPalindrome(string & s) {
	n = s.size();
	int c = 1, r = 2;
	p[0] = 1; p[1] = 2;
	for (int i = 2; i < 2 * n + 1; i++) {
		if (i < r)
			p[i] = min(r - i, p[2 * c - i]);
		else
			p[i] = 0;
		while (i + p[i] < 2 * n + 1 && i - p[i] >= 0 && ((i + p[i]) % 2 == 0 || s[(i + p[i]) / 2] == s[(i - p[i]) / 2]))
			p[i]++;
		if (i + p[i] > r)
			c = i, r = i + p[i];
	}
	int l = -1, s = 0;
	for (int i = 0; i < 2 * n + 1; i++) {
		p[i] /= 2;
		if (2 * p[i] - (i % 2) > s)
			s = 2 * p[i] - (i % 2), l = (i + 1) / 2 - p[i];
	}
	return {l, s};
}