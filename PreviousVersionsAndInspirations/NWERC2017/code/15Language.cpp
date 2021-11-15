#include <bits/stdc++.h>
using namespace std;

//Ordered statistics tree
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

//GCC built-in functions
//For long long arguments add ll to the function name, e.g. __builtin_clzll(long long x)
//Returns the number of leading 0-bits in x, starting at the most significant bit position. If x is 0, the result is undefined.
int __builtin_clz (unsigned int x);

//Returns the number of trailing 0-bits in x, starting at the least significant bit position. If x is 0, the result is undefined.
int __builtin_ctz (unsigned int x);

//Returns the number of 1-bits in x.
int __builtin_popcount (unsigned int x);

//Returns one plus the index of the least significant 1-bit of x, or if x is zero, returns zero.
int __builtin_ffs (int x);

bool compFunc(int & a, int & b) {
    return a < b;
}

struct comp {
    bool operator()(int & a, int & b) {
        return compFunc(a, b);
    }
};

int main() {
    int x = 0, y = 1;
    cout << min(x, y) << " " << max(x, y) << "\n"; //0 1
    swap(x, y);
    cout << x << "\n"; //1

    //array
    int a[5];
    for (int i = 0; i < 5; i++)
        a[i] = 5 - i;
    sort(a, a + 3, compFunc);
    for (int i : a)
        cout << i << " "; //3 4 5 2 1
    cout << "\n";
    int b[5];
    memset(b, -1, sizeof b); //only for 0 and -1
    for (int i : b)
        cout << i << " "; //-1 -1 -1 -1 -1
    cout << "\n";

    //vector
    vector<int> v(a, a + 5);
    for (int i : v)
        cout << i << " "; //3 4 5 2 1
    cout << "\n";
    sort(v.rbegin(), v.rend());
    for (int i : v)
        cout << i << " "; //5 4 3 2 1
    cout << "\n";
    sort(v.begin(), v.end());
    cout << *lower_bound(v.begin(), v.end(), 2) << " " << *upper_bound(v.begin(), v.end(), 4) << "\n"; //2 5
    for (auto it = lower_bound(v.begin(), v.end(), 2); it != upper_bound(v.begin(), v.end(), 4); it++)
        cout << *it << " "; //2 3 4
    cout << "\n";
    next_permutation(v.begin(), v.end());
    for (int i : v)
        cout << i << " "; //1 2 3 5 4
    cout << "\n";
    int c = 1;
    do {
        c++;
    } while (next_permutation(v.begin(), v.end()));
    cout << c << "\n"; //120
    for (int i : v)
        cout << i << " "; //1 2 3 4 5
    cout << "\n";
    nth_element(v.begin(), v.begin() + v.size() / 2, v.end());
    cout << "Median: " << v[v.size() / 2] << "\n"; //Median: 3
    v.assign(5, 1);
    v.push_back(2); v.push_back(3); v.pop_back();
    for (int i : v)
        cout << i << " "; //1 1 1 1 1 2
    cout << "\n" << v.front() << " " << v.back() << "\n"; //1 2

    //stack and queue
    stack<int> s; queue<int> q;
    for (int i = 1; i < 5; i++)
        s.push(i), q.push(i);
    while (!s.empty())
        cout << s.top() << " ", s.pop(); //4 3 2 1
    cout << "\n";
    while (!q.empty())
        cout << q.front() << " ", q.pop(); //1 2 3 4
    cout << "\n";

    //deque
    deque<int> d;
    d.push_back(1); d.push_back(2); d.push_back(3); d.push_front(0); d.push_front(-1);
    d.pop_back(); d.pop_front();
    for (int i : d)
        cout << i << " "; //0 1 2
    cout << "\n" << d.size() << ", " << d[d.size() - 1] << " = " << d.back() << "\n"; //3, 2 = 2

    //priority queue
    priority_queue<int, vector<int>, comp> pq;
    for (int i = 0; i < 5; i++)
        pq.push((5 - i) / 2);
    for (int i = 0; i < 5; i++)
        cout << pq.top() << " ", pq.pop(); //2 2 1 1 0
    cout << "\n";

    //set (multiset for multiple insertion into set)
    set<int> se;
    for (int i = 0; i < 5; i++)
        se.insert(i);
    se.erase(3); se.erase(se.begin());
    for (auto it = se.begin(); it != se.end(); it++)
        cout << *it << " "; //1 2 4
    cout << "\n";
    cout << (se.count(3) ? "In set" : "Not in set") << "\n"; //Not in set

    //map (multimap for multiple insertion into map)
    map<char, int> m;
    for (int i = 0; i < 5; i++)
        m['a' + i] = i;
    m.erase('c');
    for (int i = 0; i < 6; i++)
        cout << m['a' + i] << " "; //0 1 0 3 4 0
    cout << "\n";
    for (pair<char, int> i : m)
        cout << i.first << "," << i.second << " "; //a,0 b,1 c,0 d,3 e,4 f,0
    cout << "\n";

    //unordered map (Hashmap) (+ equivalents for set, multiset and multimap), no ordered iterator
    unordered_map<char, int> um;
    for (int i = 0; i < 5; i++)
        um['a' + i] = i;
    um.erase('c');
    for (int i = 0; i < 6; i++)
        cout << um['a' + i] << " "; //0 1 0 3 4 0
    cout << "\n";

    //ordered set (Order statistics tree)
    ordered_set os;
    for (int i = 1; i < 5; i++)
        os.insert(i);
    os.erase(2);
    for (auto it = os.begin(); it != os.end(); it++)
        cout << *it << " "; //1 3 4
    cout << "\n" << os.order_of_key(3) << " " << *os.find_by_order(2) << "\n"; //1 4
}
