#include<bits/stdc++.h>
using namespace std;

const int N=505;
int n,m;
char g[N][N];
int dis[N][N];
bool vis[N][N];
char es[]="\\/\\/";  //'\\'表示'\'
int dx[4]={-1,-1,1,1},dy[4]={-1,1,1,-1};
int ex[4]={-1,-1,0,0},ey[4]={-1,0,0,-1};

int bfs(){
	memset(dis,0x3f,sizeof(dis));  dis[0][0]=0;
	deque < pair<int,int> > q;  q.push_back({0,0});
	while(q.size()){
		pair<int,int> t=q.front();  q.pop_front();
		int x=t.first,y=t.second;
		if(vis[x][y])  continue;
		vis[x][y]=true;
		for(int i=0;i<4;i++){
			int a=x+dx[i],b=y+dy[i];
			if(a<0||a>n||b<0||b>m)  continue;
			int ea=x+ex[i],eb=y+ey[i];
			int d=dis[x][y]+(g[ea][eb]!=es[i]);
			if(d<dis[a][b]){
				dis[a][b]=d;
				if(g[ea][eb]!=es[i])  q.push_back({a,b});
				else  q.push_front({a,b});
			}
		}
	}
	return dis[n][m];
} 

int main(){
	cin>>n>>m;
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			cin>>g[i][j];
		}
	}
	int ans=bfs();
	if(vis[n][m])  cout<<ans;
	else  cout<<"NO SOLUTION";  //注意不能到达的情况
	return 0;
}
