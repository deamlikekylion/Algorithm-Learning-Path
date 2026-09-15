//树上背包：物品之间有依赖，选一个物品的话必须选它的父节点 
#include<bits/stdc++.h>
using namespace std;
const int N=105,M=105;
int n,m,root,v[N],w[N],a[N][N],b[N],f[N][M];

void dfs(int u){
	for(int i=v[u];i<=m;i++)  f[u][i]=w[u];
	for(int i=0;i<b[u];i++){
		int s=a[u][i];  dfs(s);
		for(int j=m;j>=v[u];j--){  //体积 
			for(int k=0;k<=j-v[u];k++){  //决策 
				f[u][j]=max(f[u][j],f[u][j-k]+f[s][k]);
			}
		}
	}
} 

int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		int p;  cin>>v[i]>>w[i]>>p;
		if(p==-1)  root=i;
		else  a[p][b[p]++]=i;
	}
	dfs(root);
	cout<<f[root][m];
	return 0; 
} 