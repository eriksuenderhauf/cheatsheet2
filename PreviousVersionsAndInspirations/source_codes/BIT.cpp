int bit[M],n;
void add(int i, int v){
  for(; i <= n ; i += i & -i)
    bit[i] += v;
}
int sum(int i){
  int ret=0;
  for(; i >= 1 ; i -= i & -i)
    ret += bit[i];
  return ret;
}
