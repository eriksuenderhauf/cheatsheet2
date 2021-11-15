#define left(i) (2 * (i) + 1)
#define right(i) (2 * (i) + 2)
#define parent(i) (((i) - 1) / 2)

struct operation {
    int t = 0, v = 0;
};

const int ts = 1 << 21, to = (1 << 20) - 1;
int n, t[ts];
operation o[ts];

operation combine(operation ot, operation ob) {
    if (ot.t == 1)
        return ot;
    if (ot.t == 0)
        return ob;
    if (ob.t == 0)
        ob.t = 2, ob.v = 1;
    ob.v *= ot.v;
    return ob;
}

int getValue(int x, int l, int r) {
    return o[x].t == 1 ? o[x].v * (r - l) : o[x].t == 2 ? t[x] * o[x].v : t[x];
}

void calcValue(int x, int l, int r) {
    t[x] = getValue(left(x), l, (l + r) / 2) + getValue(right(x), (l + r) / 2, r);
}

int query(int a, int b, int x = 0, int l = 0, int r = 1 << 20) {
    if (a <= l && r <= b)
        return getValue(x, l, r);
    if (b <= l || r <= a)
        return 0;
    int m = (l + r) / 2;
    o[left(x)] = combine(o[x], o[left(x)]);
    o[right(x)] = combine(o[x], o[right(x)]);
    o[x].t = 0;
    int s = 0;
    s += query(a, b, left(x), l, m);
    s += query(a, b, right(x), m, r);
    calcValue(x, l, r);
    return s;
}

void apply(int a, int b, operation v, int x = 0, int l = 0, int r = 1 << 20) {
    if (a <= l && r <= b) {
        o[x] = combine(v, o[x]);
        return;
    }
    if (b <= l || r <= a)
        return;
    int m = (l + r) / 2;
    o[left(x)] = combine(o[x], o[left(x)]);
    o[right(x)] = combine(o[x], o[right(x)]);
    o[x].t = 0;
    apply(a, b, v, left(x), l, m);
    apply(a, b, v, right(x), m, r);
    calcValue(x, l, r);
}

void build(int x = 0, int l = 0, int r = 1 << 20) {
    if (l + 1 == r)
        return;
    int m = (l + r) / 2;
    build(left(x), l, m);
    build(right(x), m, r);
    calcValue(x, l, r);
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> t[to + i];
    build();
    int l, r, v;
    //change the numbers in the range [l, r] to v
    operation op; op.t = 1, op.v = v;
    apply(l, r + 1, op);
    //multiply all numbers in the range [l, r] with v
    operation op; op.t = 2, op.v = v;
    apply(l, r + 1, op);
    //get the sum in the range [l, r]
    query(l, r + 1);
}
