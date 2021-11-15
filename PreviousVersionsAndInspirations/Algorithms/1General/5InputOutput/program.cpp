#include <bits/stdc++.h>

using namespace std;

int n;
string s;

int main() {
  // improved speed of input and output
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  // flush output for interactive problems
  cout << n << "\n" << flush;

  // read line break when using getline after using extraction
  getline(cin, s);
  // read complete line
  getline(cin, s);
  cout << s << "\n";

  long double pi = 3.01415926535897932384626433832795;
  // default precision
  cout << "Pi: " << pi << "\n";
  // relative precision as number of digits
  cout << setprecision(10);
  cout << "Pi: " << pi << "\n";
  // absolute precision as number of digits after the comma
  cout << fixed << setprecision(10);
  cout << "Pi: " << pi << "\n";
}
