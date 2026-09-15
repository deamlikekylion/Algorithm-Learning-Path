#include<bits/stdc++.h>
using namespace std;
const double eps=1e-6;
int n;
double a[15];

double f(double x)
{
	double s=0;
	for(int i=n;i>=0;i--)  s=s*x+a[i];
	return s;
}

int main()
{
	double l,r;  scanf("%d %lf %lf",&n,&l,&r);
	for(int i=n;i>=0;i--)  scanf("%lf",a[i]);
	while((r-l)>eps){
		double k=(r-l)/3;
		double mid1=l+k,mid2=r-k;
		if(f(mid1)>f(mid2))  r=mid2;
		else  l=mid1;
	}
	printf("%.5f",l);
	return 0;
}
