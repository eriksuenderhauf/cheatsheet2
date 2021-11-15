#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000000;
int maxn = 1, mem[1000000];

int fib(int n) {
    while (maxn < n)
        mem[++maxn] = mem[maxn - 1] + mem[maxn - 2];
    return mem[n];
}

int main() {
    memset(mem, -1, sizeof mem);
    mem[0] = 0, mem[1] = 1;

    int n;
    while (cout << "Enter a number to get the n-th Fibonacci number: ", cin >> n, n >= 0 && n < 1000000)
        cout <<  << "The corresponding Fibonacci number: " << fib(n) << "\n";

    return 0;
}
