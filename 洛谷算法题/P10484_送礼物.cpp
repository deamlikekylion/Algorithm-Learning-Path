#include<bits/stdc++.h>
using namespace std;

int n,cnt=0;
long long w,g[50],b[1<<25],ans=0;  //防止溢出 

void dfs1(int u,long long s){
	if(u==n/2){
		b[cnt++]=s;  return;
	}
	dfs1(u+1,s);
	if(s+g[u]<=w)  dfs1(u+1,s+g[u]);
}

void dfs2(int u,long long s){
	if(u==n){
		ans=max(ans,*(upper_bound(b,b+cnt,w-s)-1)+s);
		return;
	}
	dfs2(u+1,s);
	if(s+g[u]<=w)  dfs2(u+1,s+g[u]);
}

int main(){
	cin>>w>>n;
	for(int i=0;i<n;i++)  cin>>g[i];
	sort(g,g+n,greater<long long>());
	dfs1(0,0);
	sort(b,b+cnt);  cnt=unique(b,b+cnt)-b;  //unique去重，注意其去重原理
	dfs2(n/2,0);  cout<<ans;
	return 0;
}
