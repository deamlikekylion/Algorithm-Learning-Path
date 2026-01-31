#include<bits/stdc++.h>
using namespace std;
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
int vis[6][6]={0};
int n,m,t,sx,sy,fx,fy,tx,ty,ans=0;

void dfs(int x,int y){
	if(x==fx&&y==fy){
		ans++;  return;
	}  
	for(int i=0;i<4;i++){
		int nx=x+dx[i],ny=y+dy[i];
		if(nx<1||nx>n||ny<1||ny>m||vis[nx][ny])  continue;
		vis[nx][ny]=1;
		dfs(nx,ny);
		vis[nx][ny]=0;
	}
}

int main(){
	cin>>n>>m>>t;
	cin>>sx>>sy>>fx>>fy;
	for(int i=0;i<t;i++){
		cin>>tx>>ty;  vis[tx][ty]=1;
	}
	vis[sx][sy]=1;
	dfs(sx,sy);
	cout<<ans;
	return 0;
}


