struct node {
    node * l = 0, * r = 0;
    int v = 0;
};

const int ts = 1 << 20;
int n, ver = 0, v[ts];
node * root[1000000];

void calcValue(node * x) {
    x->v = x->l->v + x->r->v;
}

node * copyNode(node * x) {
    node * r = new node();
    r->l = x->l;
    r->r = x->r;
    r->v = x->v;
    return r;
}

int query(node * x, int a, int b, int l = 0, int r = 1 << 20) {
    if (a <= l && r <= b)
        return x->v;
    if (b <= l || r <= a)
        return 0;
    int m = (l + r) / 2;
    int s = 0;
    s += query(x->l, a, b, l, m);
    s += query(x->r, a, b, m, r);
    return s;
}

void update(node * x, int p, int l = 0, int r = 1 << 20) {
    if (l + 1 == r) {
        x->v = v[p];
        return;
    }
    int m = (l + r) / 2;
    if (p < m) {
        x->l = copyNode(x->l);
        update(x->l, p, l, m);
    } else {
        x->r = copyNode(x->r);
        update(x->r, p, m, r);
    }
    calcValue(x);
}

void build(node * x, int l = 0, int r = 1 << 20) {
    if (l + 1 == r) {
        x->v = v[l];
        return;
    }
    int m = (l + r) / 2;
    x->l = new node();
    x->r = new node();
    build(x->l, l, m);
    build(x->r, m, r);
    calcValue(x);
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> v[i];
    root[0] = new node();
    build(root[0]);
    int a, l, r;
    //change the number at position l
    v[l] = a;
    root[ver + 1] = copyNode(root[ver]), ver++;
    update(root[ver], l);
    //get the sum in the range [l, r] of version a
    query(root[a], l, r + 1);
}
