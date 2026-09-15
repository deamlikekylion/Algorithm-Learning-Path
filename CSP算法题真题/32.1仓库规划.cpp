#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,m,a[1005][15];  cin>>n>>m;
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			cin>>a[i][j];
		}
	}
	for(int i=0;i<n;i++){
		int flag=0;
		for(int j=0;j<n;j++){
			if(j!=i){
				for(int k=0;k<m;k++){
					if(a[j][k]<=a[i][k])  break;
					if(k==m-1){
						cout<<j+1<<endl;
						flag=1;
					}
				}
			}
			if(flag)  break;
			if(i!=n-1&&j==n-1)  cout<<0<<endl;
			if(i==n-1&&j==n-2)  cout<<0<<endl;
		}
	}
	return 0;
}
