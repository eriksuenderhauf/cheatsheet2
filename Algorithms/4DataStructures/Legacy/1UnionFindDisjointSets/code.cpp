#define MAXN 100000

int n, p[MAXN], s[MAXN];

void init() {
  for (int i = 0; i < n; i++)
    p[i] = i, s[i] = 1;
}

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
  i = findSet(i), j = findSet(j);
  if (i != j) {
    if (s[i] < s[j])
      swap(i, j);
    s[i] += s[j];
    p[j] = i;
  }
}
