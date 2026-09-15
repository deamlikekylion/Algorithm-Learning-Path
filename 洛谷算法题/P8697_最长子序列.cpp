#include<bits/stdc++.h>
using namespace std;

int main(){
	int ans=0;  string a,b;  cin>>a>>b; 
	for(int i=0,j=0;i<a.size()&&j<b.size();i++)  if(a[i]==b[j])  j++,ans++;
	cout<<ans;
	return 0;
}
