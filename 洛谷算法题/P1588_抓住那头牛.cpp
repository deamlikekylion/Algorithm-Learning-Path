#include<bits/stdc++.h>
using namespace std;
const int N=100005;
int x,y,dis[N];

void bfs(){
	memset(dis,-1,sizeof(dis));  dis[x]=0;
	queue <int> q;  q.push(x);
	while(q.size()){
		int x=q.front();  q.pop();
		if(x==y){
			cout<<dis[y]<<endl;
			return;
		}
		if(x+1<N&&dis[x+1]==-1){
			dis[x+1]=dis[x]+1;  q.push(x+1);
		}
		if(x-1>0&&dis[x-1]==-1){
			dis[x-1]=dis[x]+1;  q.push(x-1);
		}
		if(x*2<N&&dis[x*2]==-1){
			dis[x*2]=dis[x]+1;  q.push(x*2);
		}
	}
}

int main(){
	int t;  cin>>t;
	while(t--){
		cin>>x>>y;
		bfs();
	} 
	return 0;
}
