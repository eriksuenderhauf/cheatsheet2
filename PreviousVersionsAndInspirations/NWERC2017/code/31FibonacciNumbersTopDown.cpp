#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000000;
int mem[100000];

int fib(int n) {
    if (n < 2)
        return n == 1;
    if (mem[n] == -1)
        mem[n] = (fib(n - 1) + fib(n - 2)) % mod;
    return mem[n];
}

int main() {
    memset(mem, -1, sizeof mem);

    int n;
    while (cout << "Enter a number to get the n-th Fibonacci number: ", cin >> n, n >= 0 && n < 100000)
        cout << "The corresponding Fibonacci number: " << fib(n) << "\n";

    return 0;
}
