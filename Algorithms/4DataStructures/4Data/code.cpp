// data (sum and length of a segment)
struct data {
  int s = 0, l = 0;
};
// operation on the data (x -> a * x + b)
struct operation {
  int a = 1, b = 0;
};
// alternatively use typedefs for simpler data and operations
// combine the data from different segments
data combine(data dl, data dr) {
  return {dl.s + dr.s, dl.l + dr.l};
}
// calculate the result of an operation on the data
data calculate(operation o, data d) {
  return {o.a * d.s + o.b * d.l, d.l};
}
// merge an operation onto another operation
operation merge(operation ot, operation ob) {
  return {ot.a * ob.a, ot.b + ot.a * ob.b};
}
