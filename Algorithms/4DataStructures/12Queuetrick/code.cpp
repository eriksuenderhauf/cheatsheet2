struct dsqueue {
  struct operation;
  struct dat {
    void undo();
    void apply(operation o);
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