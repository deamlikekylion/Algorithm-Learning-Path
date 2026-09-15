#include<bits/stdc++.h>
using namespace std;

int n,d;
int a[10005];

bool dfs(int u){
	if(u==d)  return a[u-1]==n;
	for(int i=u-1;i>=0;i--){
		int t=a[u-1]+a[i];
		if(t>n)  continue;
		a[u]=t;
		for(int j=u+1;j<=d;j++)  t*=2;
		if(t<n)  return false;
		if(dfs(u+1))  return true;
	}
	return false;
}

int main(){
	a[0]=1;
	while(cin>>n&&n!=0){
		d=1;
		while(!dfs(1))  d++;
		for(int i=0;i<d;i++)  cout<<a[i]<<" ";
	    cout<<endl;
    }
    return 0;
}
