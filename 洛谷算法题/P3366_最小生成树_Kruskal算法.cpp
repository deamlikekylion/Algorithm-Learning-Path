#include<bits/stdc++.h>
using namespace std;

const int N=5005,M=2E5+5;
int n,m,ans=0,cnt=0,fa[N];
struct edge{
	int u,v,w;
	bool operator<(const edge &t)const
	{return w<t.w;}
}e[M];

int find(int x){
	if(fa[x]==x)  return x;
	return fa[x]=find(fa[x]);
}

bool kruskal(){
	sort(e,e+m);
	for(int i=1;i<=n;i++)  fa[i]=i;
	for(int i=0;i<m;i++){
		int x=find(e[i].u),y=find(e[i].v);
		if(x!=y){
			fa[x]=y;  ans+=e[i].w;  cnt++;
		}
	}
	return cnt==n-1;
}

int main(){
	cin>>n>>m;  
	for(int i=0;i<m;i++){
		int a,b,c;  cin>>a>>b>>c;
		e[i]={a,b,c};
	}
	int t=kruskal();
	if(t)  cout<<ans;
	else  cout<<"orz";
	return 0;
}
