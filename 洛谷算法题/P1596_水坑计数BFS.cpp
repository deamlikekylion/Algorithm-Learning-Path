#include<bits/stdc++.h>
using namespace std;
char g[105][105];
int dx[8]={-1,0,1,1,1,0,-1,-1};
int dy[8]={-1,-1,-1,0,1,1,1,0};
int n,m,ans=0;

void bfs(int x,int y){
	queue< pair<int,int> > q;
	q.push({x,y});
	g[x][y]='.';
	while(q.size()){
		int tx=q.front().first,ty=q.front().second;  q.pop();
		for(int i=0;i<8;i++){
		    int nx=tx+dx[i],ny=ty+dy[i];
		    if(nx<0||nx>=n||ny<0||ny>=m||g[nx][ny]=='.')  continue;
		    g[nx][ny]='.';
		    q.push({nx,ny});
	    }
	}
}

int main(){
	cin>>n>>m;
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			cin>>g[i][j];
		}
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(g[i][j]=='W'){
				ans++;  bfs(i,j);
			}
		}
	}
	cout<<ans;
	return 0;
}

