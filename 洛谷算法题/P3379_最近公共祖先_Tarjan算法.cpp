#include<bits/stdc++.h>
using namespace std;

const int N=5e5+5;
int n,m,s,fa[N],vis[N]={0},ans[N];  //ans[i]为第i次询问的答案
vector<int> e[N];
vector<pair<int,int>> query[N];  //query[a]存入(b,i),表示第i次询问a,b的最近公共祖先

int find(int u){  //并查集路径压缩找祖先节点
	if(u==fa[u])  return u;
	return fa[u]=find(fa[u]);
}

void tarjan(int u){
	vis[u]=1;
	for(auto v : e[u]){
		if(!vis[v]){
			tarjan(v);  fa[v]=u;
		}
	}
	for(auto q : query[u]){  //对于一次询问,有两次处理的机会,必定有一次两个节点都被访问了
		int v=q.first;
		if(vis[v]){  //如果v已经被访问了,按照DFS和并查集特性
			         //find(v)指向目前被访问过的集合的最近祖先(远的祖先还为回溯)
					 //而u正在处理说明u也被访问了,u和v处于一个集合
					 //所以find(v)即为其最近公共祖先
			int i=q.second;  ans[i]=find(v);
		}
	}
}

int main(){
	cin>>n>>m>>s;  int a,b;  
	for(int i=0;i<n-1;i++){
		cin>>a>>b;
		e[a].push_back(b);
		e[b].push_back(a);
	}
	for(int i=1;i<=m;i++){
		cin>>a>>b;
		query[a].push_back({b,i});  //询问建双向边,保证后面再两个点都访问后询问
		query[b].push_back({a,i});
	}
	for(int i=1;i<=n;i++)  fa[i]=i;
	tarjan(s);
	for(int i=1;i<=m;i++)  cout<<ans[i]<<endl;
	return 0;
}
