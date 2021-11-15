#include <bits/stdc++.h>

struct cmp {
	bool operator()(int a, int b) {
		return a < b; }};

int main() {
	set<int, cmp> set;
	map<int, int, cmp> map;
	priority_queue<int, vector<int>, cmp> pq;
	
	for (int i = 1; i < 10; i++) set.insert(i);
	
	auto itlow = set.lower_bound(3); // -> 3
	auto itup = upper_bound(set.begin(), set.end(), 6, cmp()); // -> 7
	
	for (int i = 0; i < 10; ++i) map[i] = i * 10;
	
	auto it = map.find(5);
	if (it != map.end())
		printf("(%d %d)\n", it->first, it->second);
	
	int cmb[] = { 1, 2, 3 };
	do { // (1 2 3), (1 3 2), (2 1 3), (2 3 1), (3 1 2), (3 2 1)
		printf("(%d %d %d)\n", cmb[0], cmb[1], cmb[2]);
	} while (next_permutation(cmb, cmb + 3));

	// massively improve cout and cin performance for large streams
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	// Ouput a specific number of digits past the decimal point, in this case 5    
	cout.setf(ios::fixed); cout << setprecision(5);
	cout << 100.0/7.0 << endl;
	cout.unsetf(ios::fixed);
    
	// Output the decimal point and trailing zeros
	cout.setf(ios::showpoint);
	cout << 100.0 << endl;
    
	// Output a '+' before positive values
	cout.setf(ios::showpos);
	cout << 100 << " " << -100 << endl;
    
	// Output numerical values in hexadecimal
	cout << hex << 100 << " " << 1000 << " " << 10000 << dec << endl;
}