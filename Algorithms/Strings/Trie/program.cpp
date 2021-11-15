#include<bits/stdc++.h>
using namespace std;
struct trie {
  #define ep emplace_back
  vector<array<int,26>> nx;
  vector<int> isFin;
  int cnt;
  trie() : cnt(1) { add(); }
  trie(const vector<string>& s) : cnt(1) {
    add();
    for (auto x: s) ins(x);
  }
  void add() {
    cnt++, nx.ep(), isFin.ep();
  }
  void ins(const string& s) {
    int cur = 0;
    for (auto c: s) {
      if (!nx[cur][c-'a'])
        nx[cur][c-'a'] = cnt, add();
      cur = nx[cur][c-'a'];
    }
    isFin[cur]++;
  }
  void del(const string& s) {
    int cur = 0;
    for (auto c: s)
      cur = nx[cur][c-'a'];
    isFin[cur]--;
  }
  int find(const string& s) {
    int cur = 0;
    for (auto c: s) {
      if (!nx[cur][c-'a'])
        return 0;
      cur = nx[cur][c-'a'];
    }
    return isFin[cur] > 0;
  }
};
int main() {
  trie t;
  t.ins("lol");
  cout << t.find("lo") << endl; // 0
  cout << t.find("lol") << endl; // 1
  t.del("lol");
  cout << t.find("lol") << endl; // 0
}