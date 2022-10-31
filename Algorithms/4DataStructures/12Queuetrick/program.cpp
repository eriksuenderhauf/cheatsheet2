#include <bits/stdc++.h>
#define st first
#define nd second
using namespace std;

/*
solves https://codeforces.com/gym/102788/problem/D
*/

struct dsqueue {
  struct operation {
    int a = 0;
  };
  struct dat {
    vector<int> a, b = {0}, c = {1'000'000'000};
    int query() {
      return b.back();
    }
    int mn() {
      return c.back();
    }
    void undo() {
      a.pop_back();
      b.pop_back();
      c.pop_back();
    }
    void apply(operation o) {
      a.push_back(o.a);
      b.push_back(gcd(o.a, b.back()));
      c.push_back(min(o.a, c.back()));
    }
  };
  dat ds;
  vector<pair<int, operation>> a;
  int cnt = 0;
  dsqueue() {}
  void pop() {
    if (!cnt) {
      cnt = (int)a.size();
      reverse(a.begin(), a.end());
      for (auto& [t, o]: a)
        ds.undo(), t = 0;
      for (auto& [t, o]: a)
        ds.apply(o);
    }
    deque<operation> b[2];
    for (int t : {1, 0}) {
      for (int i = 0; !t ? i < (cnt & -cnt) : a.back().st; i++) {
        b[t].push_front(a.back().nd);
        a.pop_back();
        ds.undo();
      }
    }
    for (int t : {1, 0}) {
      for (auto& o: b[t]) {
        ds.apply(o);
        a.emplace_back(t, o);
      }
    }
    cnt--;
    ds.undo();
    a.pop_back();
  }
  void push(operation o) {
    a.emplace_back(1, o);
    ds.apply(o);
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int n; cin >> n;
  dsqueue d;
  while (n--) {
    char c; cin >> c;
    if (c == '+') {
      int x; cin >> x;
      d.push({x});
    } else if (c == '-')
      d.pop();
    else {
      int g = d.ds.query();
      if (g == d.ds.mn())
        cout << "Y" << g << "\n";
      else
        cout << "N\n";
    }
  }
}