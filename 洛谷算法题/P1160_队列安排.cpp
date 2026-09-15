#include<bits/stdc++.h>
using namespace std;
struct node{
	int preid,nextid;
}a[100050];
int b[100050]={0};
int main(){
	int n,m,x,y,t=0;  cin>>n;
	a[0].nextid=1;  a[1].preid=0;  a[1].nextid=-1;
	for(int i=2;i<=n;i++){
		cin>>x>>y;
		if(y==0){
			a[i].nextid=x;
			a[i].preid=a[x].preid;
			a[a[x].preid].nextid=i;
			a[x].preid=i;
		}else{
			a[i].preid=x;
			a[i].nextid=a[x].nextid;
			a[a[x].nextid].preid=i;
			a[x].nextid=i;
		}
	}
	cin>>m;
	while(m--){
		cin>>x; 
		if(b[x]==0){
			a[a[x].preid].nextid=a[x].nextid;
		    a[a[x].nextid].preid=a[x].preid;
		    b[x]=1;
		} 
	}
	while(t>=0){
		t=a[t].nextid;
		if(t>0&&a[t].nextid!=-1)  cout<<t<<" ";
		else if(t>0)  cout<<t;
	}
	return 0;
}
