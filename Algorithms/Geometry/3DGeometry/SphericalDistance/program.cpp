#include <bits/stdc++.h>

using namespace std;

double sphericalDistance(double f1, double t1,
		double f2, double t2, double radius) {
	double dx = sin(t2)*cos(f2) - sin(t1)*cos(f1);
	double dy = sin(t2)*sin(f2) - sin(t1)*sin(f1);
	double dz = cos(t2) - cos(t1);
	double d = sqrt(dx*dx + dy*dy + dz*dz);
	return radius*2*asin(d/2);
}

const double M_PI = acos(-1);

int main() {
	// Speed input/output up significantly
	ios_base::sync_with_stdio(false);

	cout << " Spherical distance: " <<  sphericalDistance(0, 0, 0, M_PI / 2, 1) << endl;
	return 0;
}
