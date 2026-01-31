#include<bits/stdc++.h>
using namespace std;

const int N=20,INF=1e9;
int n,m,ans=INF;
int minv[N],mins[N];

void dfs(int u,int R,int H,int v,int s){
	if(u==0){
		if(v==n)  ans=min(ans,s);
		return;
	}
	if(v+minv[u]>n)  return;
	if(s+mins[u]>=ans)  return;
	if(s+2*(n-v)/R>=ans)  return;
	for(int r=min(R-1,(int)sqrt(n-v));r>=u;r--){
		for(int h=min(H-1,(n-v)/(r*r));h>=u;h--){
			dfs(u-1,r,h,v+r*r*h,s+2*r*h+(u==m?r*r:0));
		}
	}
}

int main(){
	cin>>n>>m;  minv[0]=mins[0]=0;
	for(int i=1;i<=m;i++){
		minv[i]=minv[i-1]+i*i*i;
		mins[i]=mins[i-1]+2*i*i;
	}
	dfs(m,INF,INF,0,0);
	if(ans==INF)  ans=0;
	cout<<ans;
	return 0;
}
