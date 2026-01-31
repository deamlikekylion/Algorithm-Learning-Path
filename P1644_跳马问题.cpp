#include<bits/stdc++.h>
using namespace std;
int dy[4]={1,2,1,2};
int dx[4]={2,1,-2,-1};
int n,m,ans=0;

void dfs(int x,int y){
	if(x==n&&y==m){
		ans++;  return;
	}
	for(int i=0;i<4;i++){
		int nx=x+dx[i],ny=y+dy[i];
		if(nx<0||nx>n||ny>m)  continue;
		dfs(nx,ny);
	}
} 

int main(){
	cin>>n>>m;
	dfs(0,0);
	cout<<ans;
	return 0;
}

