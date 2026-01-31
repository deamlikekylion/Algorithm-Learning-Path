#include<bits/stdc++.h>   //本质为子集和问题：寻找不超过c的最大子集和 
using namespace std;
long long n,c,a[1005],sum[1005],ans=0;

void dfs(int now,long long w){
	if(w>c)  return;
	if(sum[now-1]+w<=c){
		ans=max(ans,sum[now-1]+w);
		return;
	}
	ans=max(ans,w);
	for(int i=1;i<now;i++)  dfs(i,w+a[i]);
	return;
}

int main(){
	cin>>n>>c;  sum[0]=0;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		sum[i]=sum[i-1]+a[i];
	}
	dfs(n+1,0);
	cout<<ans<<endl;
	return 0;
}
