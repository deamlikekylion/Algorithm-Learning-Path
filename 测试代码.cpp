#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
int A,B,C,m,i,j,k,a[N],c[N];
int sx[N],sy[N],sz[N],tx[N],ty[N],tz[N],h[N];
int l,r,mid;
int calc(int a,int b,int c)
{
	return max(0ll,((a-1)*B+(b-1))*C+(c-1)+1);
}
void cf(int sx,int sy,int sz,int tx,int ty,int tz,int h)
{
	c[calc(sx,sy,sz)]+=h;
	c[calc(tx+1,sy,sz)]-=h;
	c[calc(sx,ty+1,sz)]-=h;
	c[calc(sx,sy,tz+1)]-=h;
	c[calc(sx,ty+1,tz+1)]+=h;
	c[calc(tx+1,sy,tz+1)]+=h;
	c[calc(tx+1,ty+1,sz)]+=h;
	c[calc(tx+1,ty+1,tz+1)]-=h;
}
bool check(int mid)
{
	memset(c,0,sizeof(c));
	int i,j,k;
	for (i=1;i<=mid;i++) cf(sx[i],sy[i],sz[i],tx[i],ty[i],tz[i],h[i]);
	for (i=1;i<=A;i++)
	{
		for (j=1;j<=B;j++)
		{
			for (k=1;k<=C;k++)
			{
				c[calc(i,j,k)]+=
    			c[calc(i-1,j,k)]
    			+c[calc(i,j-1,k)]
    			+c[calc(i,j,k-1)]
    			-c[calc(i-1,j-1,k)]
    			-c[calc(i-1,j,k-1)]
    			-c[calc(i,j-1,k-1)]
    			+c[calc(i-1,j-1,k-1)];
				if (c[calc(i,j,k)]>a[calc(i,j,k)]) return true; 
			}
		}
	}
	return false;
}
signed main()
{
	scanf("%lld%lld%lld%lld",&A,&B,&C,&m);
	for (i=1;i<=A;i++)
	{
		for (j=1;j<=B;j++)
		{
			for (k=1;k<=C;k++) scanf("%lld",&a[calc(i,j,k)]);
		}
	}
	for (i=1;i<=m;i++) scanf("%lld%lld%lld%lld%lld%lld%lld",&sx[i],&tx[i],&sy[i],&ty[i],&sz[i],&tz[i],&h[i]);
	l=1;
	r=m;
	while (l<=r)
	{
		mid=l+r>>1;
		if (check(mid)) r=mid-1;
		else l=mid+1;
	}
	printf("%lld",l);
	return 0;
}
