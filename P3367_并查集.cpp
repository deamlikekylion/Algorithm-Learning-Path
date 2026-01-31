#include<bits/stdc++.h>
using namespace std;

const int N=2e5+5;
int n,m,fa[N];

int find(int x){
	if(fa[x]==x)  return x;
	return fa[x]=find(fa[x]);
}

void unionset(int x,int y){
	fa[find(x)]=find(y);
}

int main(){
	cin>>n>>m;  int x,y,z;
	for(int i=1;i<=n;i++)  fa[i]=i;
	while(m--){
		cin>>z>>x>>y;
		if(z==1)  unionset(x,y);
		else{
			x=find(x),y=find(y);
			if(x==y)  cout<<"Y"<<endl;
			else  cout<<"N"<<endl;
		}
	}
	return 0;
}
