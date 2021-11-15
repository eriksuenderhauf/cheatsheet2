int n, lrs, rsp, suf[100000], sra[100000], lcp[100000], tsu[100000], tsr[100000], tlp[100000], c[100000], phi[100000];
string s;

void countingSort(int k) {
    memset(c, 0, sizeof c);
    int mra = 0, sum = 0, tmp = 0;
    for (int i = 0; i < n; i++)
        c[i + k < n ? sra[i + k] : 0]++, mra = max(mra, i + k < n ? sra[i + k] : 0);
    for (int i = 0; i <= mra; i++)
        tmp = sum + c[i], c[i] = sum, sum = tmp;
    for (int i = 0; i < n; i++)
        tsu[c[suf[i] + k < n ? sra[suf[i] + k] : 0]++] = suf[i];
    for (int i = 0; i < n; i++)
        suf[i] = tsu[i];
}

void suffixArray() {
    for (int i = 0; i < n; i++) {
        suf[i] = i;
        sra[i] = s[i];
    }
    for (int k = 1; k < n; k <<= 1) {
        countingSort(k);
        countingSort(0);
        tsr[suf[0]] = 0;
        for (int i = 1; i < n; i++)
            tsr[suf[i]] = tsr[suf[i - 1]] +
                ((sra[suf[i]] == sra[suf[i - 1]] && (suf[i] + k < n ? sra[suf[i] + k] : -1) ==
                  (suf[i - 1] + k < n ? sra[suf[i - 1] + k] : -1)) ? 0 : 1);
        for (int i = 0; i < n; i++)
            sra[i] = tsr[i];
        if (sra[suf[n - 1]] == n - 1)
            break;
    }
}

int findString(string & p, bool eql) {
    int l = 0, r = n - 1;
    while (l < r) {
        int m = (l + r) / 2;
        int res = strncmp(& s.front() + suf[m], & p.front(), p.size());
        if (res > 0 || eql && res == 0)
            r = m;
        else
            l = m + 1;
    }
    int res = strncmp(& s.front() + suf[l], & p.front(), p.size());
    if (res < 0 || !eql && res == 0)
        l++;
    return l;
}

vector<int> findMatches(string & p) {
    int l = findString(p, true), r = findString(p, false);
    vector<int> res;
    for (int i = l; i < r; i++)
        res.push_back(suf[i]);
    return res;
}

void longestCommonPrefix() {
    phi[suf[0]] = -1;
    for (int i = 1; i < n; i++)
        phi[suf[i]] = suf[i - 1];
    int l = 0;
    for (int i = 0; i < n; i++) {
        if (phi[i] == -1) {
            tlp[i] = 0;
            continue;
        }
        while (i + l < n && phi[i] + l < n && s[i + l] == s[phi[i] + l])
            l++;
        tlp[i] = l;
        l = max(l - 1, 0);
    }
    for (int i = 0; i < n; i++) {
        lcp[i] = tlp[suf[i]];
        if (lcp[i] > lrs)
            lrs = lcp[i], rsp = suf[i];
    }
}

int main() {
    cin >> s;
    n = s.size();

    suffixArray();
    longestCommonPrefix();

    string p;
    //match a pattern
    vector<int> ind = findMatches(p);
    //the size of the longest repeated substring
    lrs;
    //the index of the longest repeated substring
    rsp;
}
