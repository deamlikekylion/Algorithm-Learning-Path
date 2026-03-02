#include"bits/stdc++.h"
#define N 1005
#define M 55
#define int long long
using namespace std;
int read()
{
	int x = 0, fff = 1;
	char c;
	while ((c = getchar()) < '0' || c > '9')
		if (c == '-')
			fff = -1;
	while (c >= '0' && c <= '9')
		x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
	return x * fff;
}
const int mod=1e8+7;
int n,s,a,b;
int dp[N][N];
signed main()
{
	n=read();
	s=read(),a=read(),b=read();
	dp[0][0]=1;
	for(int i=1;i<n;i++) 
		for(int j=0;j<n;j++)
			dp[i][j]=(dp[i-1][((j-i*a)%n+n)%n]+dp[i-1][((j+i*b)%n+n)%n])%mod;
	printf("%lld\n",dp[n-1][(s%n+n)%n]);
	return 0;
}
