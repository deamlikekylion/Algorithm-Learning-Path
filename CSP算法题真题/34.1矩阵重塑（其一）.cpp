#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,m,p,q;  cin>>n>>m>>p>>q;
	int a[10010],k=0;
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			scanf("%d",&a[k++]);
		}
	}
	k=0;
	for(int i=0;i<p;i++){
		for(int j=0;j<q;j++){
			printf("%d ",a[k++]);
		}
		cout<<endl;
	} 
	return 0;
}
