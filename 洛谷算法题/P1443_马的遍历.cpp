#include<bits/stdc++.h>
using namespace std;
int dx[8]={-2,-2,-1,-1,1,1,2,2};
int dy[8]={-1,1,-2,2,-2,2,-1,1};
queue< pair<int,int> > q;
int f[405][405];
bool vis[405][405];

int main(){
	int n,m,x,y;
	memset(f,-1,sizeof(f));  memset(vis,false,sizeof(vis));
	cin>>n>>m>>x>>y;
	f[x][y]=0;  vis[x][y]=true;  q.push(make_pair(x,y)); //
	while(!q.empty()){
		int xx=q.front().first,yy=q.front().second;  q.pop();
		for(int i=0;i<8;i++){
			int nx=xx+dx[i],ny=yy+dy[i];
			if(nx<1||nx>n||ny<1||ny>m||vis[nx][ny])  continue;
			vis[nx][ny]=true;  q.push({nx,ny});  //make_pair(x,y)或{x,y} 
			f[nx][ny]=f[xx][yy]+1;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			printf("%-5d",f[i][j]);
		}
		cout<<endl;
	}
	return 0;
}













