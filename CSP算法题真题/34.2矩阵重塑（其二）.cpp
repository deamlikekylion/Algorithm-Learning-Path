#include<bits/stdc++.h>
using namespace std;
int main(){
	int a[2][10010],n,m,t,k=0,b=0,op;
	cin>>n>>m>>t;
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			cin>>a[b][k++];
		}
	}
	while(t--){
		cin>>op;
		if(op==1){
			int p,q;  cin>>p>>q;  n=p;  m=q;
		}
		if(op==2){
			int c,d;  cin>>c>>d;
			for(int i=0;i<m;i++){
				d=i;
				for(int j=0;j<n;j++){
					a[!b][c++]=a[b][d];
					d+=m;
				}
			}
			c=n; n=m; m=c;
			b=!b;
		}
		if(op==3){
			int i,j;  cin>>i>>j;
			int x=i*m+j;
			printf("%d\n",a[b][x]);
		}
	}
	return 0;
}
