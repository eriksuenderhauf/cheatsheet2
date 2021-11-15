int n, m, r[1000000];
string s;

void preprocessPattern(string & p) {
    int j = -1;
    r[0] = -1;
    for (int i = 0; i < m; i++) {
        while (j >= 0 && p[i] != p[j])
            j = r[j];
        r[i + 1] = ++j;
    }
}

vector<int> findMatches(string & p) {
    preprocessPattern(p);
    int j = 0;
    vector<int> res;
    for (int i = 0; i < n; i++) {
        while (j >= 0 && s[i] != p[j])
            j = r[j];
        j++;
        if (j == m)
            res.push_back(i - j + 1), j = r[j];
    }
    return res;
}

int main() {
    cin >> s;
    n = s.size();

    string p;
    //match a pattern
    m = p.size();
    vector<int> ind = findMatches(p);
}
