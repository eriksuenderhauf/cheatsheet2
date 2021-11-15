#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ost; // null_mapped_type instead of null_type in older versions

int main() {
	ost X;
	for(int i = 0; i < 100; i += 10)
		X.insert(i); // insert 0, 10,..., 90

	cout << X.order_of_key(30) << endl;
	// result: 3 (number of keys < 30)
	cout << X.order_of_key(31) << endl;
	// result: 4 (number of keys < 31)
	cout << *X.find_by_order(3) << endl;
	// result: 30 (3th element (0-based))

	// first >= 30 (lower) and > 30 (upper)
	cout << *X.lower_bound(30) << endl; // 30
	cout << *X.upper_bound(30) << endl; // 40

	X.erase(20); // remove element
	return 0;
}
