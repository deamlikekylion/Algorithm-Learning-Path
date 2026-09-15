#include<bits/stdc++.h>
using namespace std;

int main(){
	int n,m;  cin>>n>>m;
	int f[105]={0},c[105],mod=1e9+7;
	for(int i=0;i<=m;i++)  c[i]=1;
	for(int i=1;i<=n;i++){
		int v,w;  cin>>v>>w;
		for(int j=m;j>=v;j--){
			if(f[j-v]+w>f[j]){
				f[j]=f[j-v]+w;
				c[j]=c[j-v];
			}else if(f[j-v]+w==f[j]){
				c[j]=(c[j]+c[j-v])%mod;
			}
		}
	} 
	cout<<c[m];
	return 0; 
} 
