#define MAXN 100000

int n, a[MAXN];

// get the indices of the maximum elements in all ranges of size k
vector<int> getIndicesOfMaxima(int k) {
  vector<int> r;
  deque<int> d;
  for (int i = 0; i < n; i++) {
    while (!d.empty() && i - d.front() >= k)
      d.pop_front();
    while (!d.empty() && a[i] >= a[d.back()])
      d.pop_back();
    d.push_back(i);
    if (i >= k - 1)
      r.push_back(d.front());
  }
  return r;
}
