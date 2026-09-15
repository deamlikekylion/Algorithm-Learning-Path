#include<bits/stdc++.h>
using namespace std;

const int N=6e3+5;
int n,w[N],fa[N],f[N][2];
vector<int> g[N];

void dfs(int u){
	f[u][1]=w[u];
	for(int v : g[u]){
		dfs(v);
		f[u][0]+=max(f[v][0],f[v][1]);
		f[u][1]+=f[v][0];
	}
} 

int main(){
	cin>>n;  for(int i=1;i<=n;i++)  cin>>w[i];
	for(int i=0;i<n-1;i++){
		int x,y;  cin>>x>>y;
		g[y].push_back(x);
	    fa[x]=y;
	}
	int root=1;  while(fa[root])  root++;
	dfs(root);
	cout<<max(f[root][0],f[root][1]);
	return 0;
}
