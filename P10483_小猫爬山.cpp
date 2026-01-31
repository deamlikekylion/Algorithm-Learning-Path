#include<bits/stdc++.h>
using namespace std;

const int N=23;
int n,w,ans,cnt=0;
int c[N],sum[N];

void dfs(int u){
	if(cnt>=ans)  return;
	if(u==n){
		ans=cnt;  return;
	}
	for(int i=0;i<cnt;i++){
		if(sum[i]+c[u]<=w){
			sum[i]+=c[u];
			dfs(u+1);
			sum[i]-=c[u];
		}
	}
	sum[cnt++]=c[u];
	dfs(u+1);
	sum[--cnt]=0;
}

int main(){
	cin>>n>>w;  ans=n;
	for(int i=0;i<n;i++)  cin>>c[i];
	sort(c,c+n,greater<int>());
	dfs(0);
	cout<<ans;
	return 0;
}
