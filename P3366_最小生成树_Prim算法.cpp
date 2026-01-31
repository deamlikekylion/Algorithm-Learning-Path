#include<bits/stdc++.h>
using namespace std;

const int N=5005,INF=1e8;
int n,m,ans=0,cnt=0;
struct edge{
	int v,w;
};
vector<edge> e[N];
int d[N],vis[N];
priority_queue<pair<int,int>> q;

bool prim(int s){
	for(int i=1;i<=n;i++)  d[i]=INF;
	d[s]=0;  q.push({0,s});
	while(q.size()){
		int u=q.top().second;  q.pop();
		if(vis[u])  continue;
		vis[u]=1;  cnt++;  ans+=d[u];
		for(auto ed : e[u]){
			int v=ed.v,w=ed.w;
			if(d[v]>w){
				d[v]=w;  q.push({-d[v],v});
			}
		}
	}
	return cnt==n;
}

int main(){
	cin>>n>>m;  
	for(int i=0;i<m;i++){
		int a,b,c;  cin>>a>>b>>c;
		e[a].push_back({b,c});
		e[b].push_back({a,c});
	}
	int t=prim(1);
	if(t)  cout<<ans;
	else  cout<<"orz";
	return 0;
}
