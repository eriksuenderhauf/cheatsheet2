int n, p[1000000], s[1000000];

int findSet(int i) {
    return p[i] == i ? i : (p[i] = findSet(p[i]));
}

bool inSameSet(int i, int j) {
    return findSet(i) == findSet(j);
}

int getSizeOfSet(int i) {
    return s[findSet(i)];
}

void unionSet(int i, int j) {
    if (!inSameSet(i, j))
        s[findSet(j)] += s[findSet(i)], p[findSet(i)] = findSet(j);
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++)
        p[i] = i, s[i] = 1;
}
