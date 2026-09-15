#include<bits/stdc++.h>
using namespace std;

const int N=1005,INF=0x3f3f3f3f;
int n,m,d[N][N],p[N][N];

void floyd(){
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(d[i][j]>d[i][k]+d[k][j]){
					d[i][j]=d[i][k]+d[k][j];
					p[i][j]=k;
				}
			}
		}
	}
}

void path(int i,int j){
	if(p[i][j]==0)  return;
	int k=p[i][j];
	path(i,k);
	cout<<" "<<k;
	path(k,j);
}

int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i==j)  d[i][j]=0;
			else  d[i][j]=INF;
		}
	}
	for(int i=0;i<m;i++){
		int a,b,c;  
		cin>>a>>b>>c;
		d[a][b]=c;
	}
	floyd(); 
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i==j)  continue;
			if(d[i][j]==INF)  cout<<"从"<<i<<"到"<<j<<"不可达！"<<endl;
			else{
				cout<<"从"<<i<<"到"<<j<<"的最短距离为："<<d[i][j];
				cout<<"，最短路径为："<<i;  path(i,j);  cout<<" "<<j<<endl;
			} 
		}
	}
	return 0;
}