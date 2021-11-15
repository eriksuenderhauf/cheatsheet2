#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);

    int n; string s;
    cin >> n;

    //line break must be read before using getline
    getline(cin, s);
    for (int i = 0; i < n; i++)
        getline(cin, s), cout << s << "\n" << flush;

    long double pi = 3.01415926535897932384626433832795;
    //fixed number of digits after comma in the output
    cout << fixed << setprecision(10);
    cout << "Pi: " << pi << "\n";
}
