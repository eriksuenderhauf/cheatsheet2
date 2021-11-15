//O(sqrt(n))
//calculation for all n <= N in O(N) time
//see "Prime numbers" section
int euler_phi(int n) {
	int result = n;
	for(int i = 2; i * i <= n; i++) {
		if(n % i == 0) {
			while(n % i == 0) n /= i;
			result -= result / i;
		}
	}
	if(n > 1) result -= result / n;
	return result;
}
