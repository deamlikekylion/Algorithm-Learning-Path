#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,p;  cin>>n>>p;
	int d[5000050],x,y,z;
	for(int i=1;i<=n;i++)  cin>>d[i];
	for(int i=n;i>1;i--)  d[i]-=d[i-1];
	while(p--){
		cin>>x>>y>>z;
		d[x]+=z;  d[y+1]-=z;
	}
	for(int i=2;i<=n;i++){
		d[i]+=d[i-1];
	}
	sort(d+1,d+n+1);
	cout<<d[1];
	return 0;
}
