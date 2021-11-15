#include <bits/stdc++.h>
using namespace std;

// Story: - You have a queue of passengers p1, p2... p_n waiting for gondolas
//		  - You should pack them in k gondolas, in the order listed
//		  - Packing passengers i to j into one gondola costs C[i][j]
//		  - minimize the cost
// 		  - Sufficient constraint on cost function: 
// 			C[a][c] + C[b][d] <= C[a][d] + C[b][c], a < b < c < d (typically satisfied) 
//			means longer intervals cost more than smaller ones
// Refinement: in our story (not necessary) in every gondola needs to be at least one person 

int LARGE = 100000000;

int U[4009][4009];
int C(int i, int j)
{
	return U[j][j] - U[i - 1][j] - U[j][i - 1] + U[i - 1][i - 1];	
}

// -> to compute
int f(int i, int j)
{
	if(i == 0) return j == 0 ? 0 : LARGE;
	if(j == 0) return LARGE;
	
	int result = LARGE;
	for(int k = 0; k < j; k++)
		result = min(result, f(i - 1, k) + C(k + 1, j));
	return result;
}

// Trick:
//			Define opt[i][j] := smallest k such that f(i, j) = f(i - 1, k) + C(k + 1, j)
//			i.e. "position" of the optimal solution where you perfere to take the most
//			notice that opt[i][1] <= opt[i][2] <= opt[i][3] ...
// 			thus if we want to calculate all values [f(i, a), f(i, a + 1) .. f(i, b)] 
//			we have a restriction on the possible search range, as we do not have to search
// 			for an optimal solution at k < opt[i][b + 1]
// 			The following has runtime O(k*n*log(n))


int dp[4009][4009];

void divConq(int i, int a, int b, int optL, int optR)
{
	if(a > b) return;
	
	int m = (a + b) / 2, opt;

	// calculate value for the middle element - as in f
	dp[i][m] = LARGE;
	for(int k = optL; k <= optR; k++)
		if(dp[i - 1][k] + C(k + 1, m) <= dp[i][m])
		{
			dp[i][m] = dp[i - 1][k] + C(k + 1, m);
			opt = k;
		}
		
	divConq(i, a, m - 1, optL, opt);
	divConq(i, m + 1, b, opt, optR);
}

int dpOpt(int k, int n)
{
	for(int i = 0; i <= k; i++)
	{
		if(i == 0) 
		{
			for(int j = 0; j <= n; j++) 
				dp[i][j] = j == 0 ? 0 : LARGE;
				continue;
		}
		dp[i][0] = LARGE;
		
		divConq(i, 1, n, 0, n);
	}
	
	return dp[k][n];
}

