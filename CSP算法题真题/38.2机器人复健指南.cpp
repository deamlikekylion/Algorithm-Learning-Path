#include<bits/stdc++.h>
using namespace std;

int n,k,x,y,cnt,ans;
int vis[110][110];
int dx[8]={-2,-1,1,2,-2,-1,1,2};
int dy[8]={1,2,2,1,-1,-2,-2,-1};

void dfs(int x,int y){  // 加一个u表示层数dfs(x,y,u) 后面有时间改一下 
	vis[x][y]=1;  ans++;  cnt++;
	if(cnt>k)  return;
	for(int i=0;i<8;i++){
		int nx=x+dx[i],ny=y+dy[i];
		if(nx>=1&&nx<=n&&ny>=1&&ny<=n&&!vis[nx][ny]){
		    dfs(nx,ny);  cnt--; 
		}
	}
	return;
}

int main(){
	cin>>n>>k>>x>>y;  
	dfs(x,y);
	cout<<ans;
	return 0;
}