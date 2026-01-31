#include<bits/stdc++.h>
using namespace std;

int main(){
	int n,m,w[105][105],d[105][105];
	cin>>n>>m;  int ans=1e8;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i!=j)  w[i][j]=1e8;
			else  w[i][j]=0;
		}
	}
	for(int i=0;i<m;i++){
		int a,b,c;  cin>>a>>b>>c;
		w[a][b]=w[b][a]=c;
	}
	memcpy(d,w,sizeof(d));
	for(int k=1;k<=n;k++){
		for(int i=1;i<k;i++){
			for(int j=i+1;j<k;j++){
				ans=min(ans,d[i][j]+w[j][k]+w[k][i]);
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
			}
		}
	}
	if(ans==1e8)  cout<<"No solution.";
	else  cout<<ans;
	return 0;
}
