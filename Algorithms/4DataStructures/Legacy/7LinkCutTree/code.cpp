// the data with default values
struct data {
  int v = 0, s = 0, o = 0;
};

// the operation with default values
// this default operation applies a * v + b to every element v
struct operation {
  int a = 1, b = 0;
};

struct node {
  node * u = 0, * p = 0, * l = 0, * r = 0;
  bool i = false;
  data t;
  operation o;
};

// combine the data from different branches
data combine(data o, data l, data r) {
  return {o.o + l.v + r.v, 1 + l.s + r.s, o.o};
}

// apply an operation on top of an other operation
operation combine(operation ot, operation ob) {
  return {ot.a * ob.a, ot.b + ot.a * ob.b};
}

// apply an operation on a range with data
data apply(operation ot, data d) {
  return {ot.a * d.v + ot.b * d.s, d.s, ot.a * d.o + ot.b};
}

data getValue(node * x) {
  if (x == 0)
    return data();
  return apply(x->o, x->t);
}

void calcValue(node * x) {
  x->t = combine(x->t, getValue(x->l), getValue(x->r));
}

void propagate(node * x) {
  if (x->i) {
    swap(x->l, x->r), x->i = false;
    if (x->l != 0)
      x->l->i = !x->l->i;
    if (x->r != 0)
      x->r->i = !x->r->i;
  }
  if (x->l != 0)
    x->l->o = combine(x->o, x->l->o);
  if (x->r != 0)
    x->r->o = combine(x->o, x->r->o);
  x->t = apply(x->o, x->t);
  x->o = operation();
}

void zig(node * x) {
  node * p = x->p;
  if (x->p->l == x) {
    p->l = x->r;
    if (p->l != 0)
      p->l->p = p;
    x->r = p;
  } else {
    p->r = x->l;
    if (p->r != 0)
      p->r->p = p;
    x->l = p;
  }
  x->p = p->p;
  if (x->p != 0)
    if (x->p->l == p)
      x->p->l = x;
    else
      x->p->r = x;
  p->p = x;
  x->u = p->u;
  p->u = 0;
  calcValue(p);
  calcValue(x);
}

void zigzig(node * x) {
  zig(x->p);
  zig(x);
}

void zigzag(node * x) {
  zig(x);
  zig(x);
}

void splay(node * x) {
  propagate(x);
  while (x->p != 0) {
    if (x->p->p != 0)
      propagate(x->p->p);
    propagate(x->p);
    propagate(x);
    if (x->p->p == 0)
      zig(x);
    else if (x->p->l == x && x->p->p->l == x->p || x->p->r == x && x->p->p->r == x->p)
      zigzig(x);
    else
      zigzag(x);
  }
}

node * getLeftmost(node * x) {
  propagate(x);
  while (x->l != 0)
    x = x->l, propagate(x);
  splay(x);
  return x;
}

node * getRightmost(node * x) {
  propagate(x);
  while (x->r != 0)
    x = x->r, propagate(x);
  splay(x);
  return x;
}

node * getLeft(node * x) {
  splay(x);
  if (x->l == 0)
    return 0;
  return getRightmost(x->l);
}

node * splitRight(node * x) {
  splay(x);
  node * r = x->r;
  x->r = 0;
  if (r != 0)
    r->p = 0;
  calcValue(x);
  return r;
}

node * merge(node * l, node * r, bool lu = true) {
  if (l == 0)
    return r;
  if (r == 0)
    return l;
  splay(l);
  l = getRightmost(l);
  splay(r);
  r = getLeftmost(r);
  if (lu) {
    l->r = r;
    r->p = l;
    r->u = 0;
    calcValue(l);
    return l;
  } else {
    r->l = l;
    l->p = r;
    l->u = 0;
    calcValue(r);
    return r;
  }
}

void expose(node * x) {
  node * r = splitRight(x);
  if (r != 0)
    r->u = x;
  while (x->u != 0) {
    r = splitRight(x->u);
    if (r != 0)
      r->u = x->u;
    merge(x->u, x, true);
    splay(x);
  }
}

// get the root of the tree
node * getRoot(node * x) {
  expose(x);
  splay(x);
  return getLeftmost(x);
}

// make x the new root of the tree
void reroot(node * x) {
  expose(x);
  splay(x);
  x->i = !x->i;
}

// cut the link between x and its parent
void cut(node * x) {
  expose(x);
  node * l = getLeft(x);
  if (l == 0)
    return;
  expose(l);
  splay(x);
  x->u = 0;
}

// cut the link between x and y
void cut(node * x, node * y) {
  reroot(x);
  cut(y);
}

// set the parent of x to p
void link(node * x, node * p) {
  reroot(x);
  splay(x);
  x->u = p;
}

// query the data along the path from x to y
data queryPath(node * x, node * y) {
  reroot(x);
  expose(y);
  splay(x);
  return x->t;
}

// apply an operation along the path from x to y
void applyPath(node * x, node * y, operation o) {
  reroot(x);
  expose(y);
  splay(x);
  x->o = combine(o, x->o);
}

bool inSameComponent(node * x, node * y) {
  return getRoot(x) == getRoot(y);
}
