#include<bits/stdc++.h>
using namespace std;
char mat[8][8],vis[8][8];
int n,m,t,a,b,c,d,flag;
int dx[4]={1,-1,0,0};
int dy[4]={0,0,1,-1};

void dfs(int x,int y,int time){
	if(flag)  return;
	if(mat[x][y]=='D'){
		if(time==t)  flag==1;
		return;
	}
	int tmp=t-time-abs(c-x)-abs(d-y);
	if(tmp<0)  return;
	for(int i=0;i<4;i++){
		int nx=x+dx[i],ny=y+dy[i];
		if(nx>=0&&nx<n&&ny>=0&&ny<m&&mat[nx][ny]!='X'&&!vis[nx][ny]){
			vis[nx][ny]=1;
			dfs(nx,ny,time+1);
			vis[nx][ny]=0;
		}
	}
	return;
}

int main(){
	while(~scanf("%d %d %d",&n,&m,&t)){
		if(n==0&&m==0&&t==0)  break;
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				cin>>mat[i][j];
				if(mat[i][j]=='S')  a=i,b=j;
				if(mat[i][j]=='D')  c=i,d=j;
			}
		}
		memset(vis,0,sizeof(vis));
		int tmp=t-abs(a-c)-abs(b-d);
		if(tmp%2){
			cout<<"NO"<<endl;  continue;
		}
		flag=0;  vis[a][b]=1;
		dfs(a,b,0);
		if(flag)  cout<<"YES"<<endl;
		else  cout<<"NO"<<endl;
	}
	return 0;
}
