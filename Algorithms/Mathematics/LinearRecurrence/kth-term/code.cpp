const int MAX_N = 2005; //a little larger
const int MOD = 1000000007; 

int n,p[MAX_N],a[MAX_N];

// to improve constant factor compute mod MOD*MOD, if that fits in ll
void mul(ll *a, ll *b)  {
	static ll t[2*MAX_N];
	fill(t,t+2*n-1,0);
	for (int i=0; i<n; i++)
		for (int j=0; j<n; j++)
			t[i+j]=(t[i+j]+a[i]*b[j])%MOD;
	for (int i=2*n-2; i>=n; i--)
		for (int j=1; j<=n; j++)
			t[i-j]=(t[i-j]+t[i]*p[j])%MOD;
	copy(t,t+n,a);
}
int kth(ll k) {
	static ll r[MAX_N],t[MAX_N];
	fill(r,r+n,0),fill(t,t+n,0);
	for (r[0]=t[1]=1; k; k/=2,mul(t,t))
		if (k&1)
			mul(r,t);
	for (int i=0; i<n; i++)
		k=(k+r[i]*a[i])%MOD;
	return k;
}
