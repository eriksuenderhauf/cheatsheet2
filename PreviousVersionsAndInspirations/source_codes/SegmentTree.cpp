// TODO: Define num_elems (~N)
const int num_elems = 1 << 20;
const int seg_size = 2 * num_elems;
const int off = num_elems - 1;
int segtree[seg_size];

int left(int x) {return 2 * x + 1;}
int right(int x) {return 2 * x + 2;}
int parent(int x) {return (x - 1) / 2;};

// TOTO: Define Operator. Example: Sum.
int op (int a, int b) {return a + b; }

void update (int pos) {
  segtree[pos] = op(segtree[left(pos)], segtree[right(pos)]);
  if (parent (pos) != pos) update(parent(pos)); }

void set (int pos, int data) {
  segtree[pos + off] = data;
  update(parent(pos + off)); }

int query (int i, int j, int l, int r, int curr_node) {
  if (i <= l && j >= r) return segtree[curr_node];
  if (i > r || j < l) return 0; // Neutral Element
  int m = (l + r) / 2;
  return op(query(i, j, l, m, left(curr_node)),
    query(i, j, m + 1, r, right(curr_node))); }

int query(int i, int j) { // op[i, j];
  return query(i, j, 0, off, 0); }

int main() {
  // Initialize
  fill_n(segtree, seg_size, 0);

return 0; }
