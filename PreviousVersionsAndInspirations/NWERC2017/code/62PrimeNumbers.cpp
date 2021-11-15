int n, prv[1000000], nxt[1000000], dvs[1000000];
vector<int> p;
bitset<1000000> ip;

bool isPrime(int x) {
    return ip[x];
}

vector<pair<int, int>> getdvsisors(int x) {
    vector<pair<int, int>> d;
    int y = dvs[x], a = 1;
    x /= dvs[x];
    while (x > 1) {
        if (dvs[x] != y) {
            d.push_back({y, a});
            y = dvs[x];
            a = 0;
        }
        x /= dvs[x], a++;
    }
    d.push_back({y, a});
    return d;
}

int main() {
    cin >> n;

    for (int i = 2; i <= n; i++)
        prv[i] = i - 1, nxt[i] = i + 1, dvs[i] = i;
    vector<int> del;
    for (int i = 2; i <= n; i = nxt[i]) {
        p.push_back(i);
        ip[i] = true;
        for (int j = i; i * j <= n; j = nxt[j])
            dvs[i * j] = i, del.push_back(i * j);
        for (int j : del)
            nxt[prv[j]] = nxt[j], prv[nxt[j]] = prv[j];
        del.clear();
    }

    //the prime numbers
    p;

    int x;
    //is prime
    isPrime(x);
    //divisors
    vector<pair<int, int>> d = getdvsisors(x);
    for (int i = 0; i < d.size(); i++)
        d[i]; //d[i].first ^ d[i].second
}
