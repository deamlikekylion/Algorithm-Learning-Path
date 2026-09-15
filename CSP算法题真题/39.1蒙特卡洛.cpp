#include<bits/stdc++.h>
using namespace std;

int main(){
	int n,a,m=0;
	cin>>n>>a;
	for(int i=0;i<n;i++){
		double b,c;  cin>>b>>c;
		if(b*b+c*c<=a*a)  m++;
	}
	double ans=4.000000000*m/n;
	printf("%.6f",ans);
	return 0;
}