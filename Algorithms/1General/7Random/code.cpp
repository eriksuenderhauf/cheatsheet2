// select seed to avoid being hacked
unsigned seed = chrono::system_clock::now().time_since_epoch().count();

mt19937 rng(seed); // random generator
uniform_int_distribution<int> unii(0, 100);
int x = unii(rng); // x in [0, 100]

uniform_real_distribution<double> unir(0.0, 1.0);
double y = unir(rng); // y in [0.0, 1.0]

bernoulli_distribution bern(0.7);
bool b = bern(rng); // true with prob. 0.7

// bin(n, p), geom(p), normal(Exp, Var^2)
binomial_distribution<int> bin(9, 0.5);
geometric_distribution<int> geom(0.3);
normal_distribution<double> normal(5.0, 2.0);

vector<int> r(10);
shuffle(r.begin(), r.end(), rng);
