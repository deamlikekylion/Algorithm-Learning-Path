#include<bits/stdc++.h>
using namespace std;

int main(){
	int n,a[5005],f[5005],ans=1;  cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];  f[i]=1;
	}
	for(int i=2;i<=n;i++){
		for(int j=1;j<i;j++){
			if(a[i]>a[j])  f[i]=max(f[i],f[j]+1);
		}
		ans=max(ans,f[i]);
	}
	cout<<ans;
	return 0;
}
