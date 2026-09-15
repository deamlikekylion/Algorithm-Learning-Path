#include<bits/stdc++.h>
using namespace std;

int main(){
	string a,b;  cin>>a>>b;
	int m=a.size(),n=b.size();
	int i,j,t1,t2,f[2005];  f[0]=0;
	for(j=1;j<=n;j++)  f[j]=j;
	for(i=1;i<=m;i++){
		t1=f[0]++;
		for(j=1;j<=n;j++){
			t2=f[j];
			if(a[i-1]==b[j-1])  f[j]=t1;
			else  f[j]=min(t1,min(f[j-1],f[j]))+1;
			t1=t2;
		}
	}
	cout<<f[n];
	return 0;
}
