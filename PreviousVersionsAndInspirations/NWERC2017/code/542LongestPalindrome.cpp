int n, p[2000000];
string s;

pair<int, int> findLongestPalindrome() {
    int c = 1, r = 2;
    p[0] = 1;
    p[1] = 2;
    for (int i = 2; i < 2 * n + 1; i++) {
        if (i < r)
            p[i] = min(r - i, p[2 * c - i]);
        else
            p[i] = 0;
        while (i + p[i] < 2 * n + 1 && i - p[i] >= 0 &&
               ((i + p[i]) % 2 == 0 || s[(i + p[i]) / 2] == s[(i - p[i]) / 2]))
            p[i]++;
        if (i + p[i] > r) {
            c = i;
            r = i + p[i];
        }
    }
    int l = -1, s = 0;
    for (int i = 0; i < 2 * n + 1; i++) {
        p[i] /= 2;
        if (i % 2 == 0 && 2 * p[i] > s || i % 2 == 1 && 2 * p[i] - 1 > s)
            s = 2 * p[i] - (i % 2 ? 1 : 0), l = (i + 1) / 2 - p[i];
    }
    return {l, s};
}

int main() {
    cin >> s;
    n = s.size();

    pair<int, int> pal = findLongestPalindrome();

    //the size of the longest palindrome
    pal.second;
    //the index of the longest palindrome
    pal.first;
}
