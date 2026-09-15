#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll p[1000];
int c[50];

int factor(ll n){
	int m=0;
	for(ll i=2;i<=sqrt(n);i++){
		if(n%i==0){
			p[++m]=i,c[m]=0;
			while(n%i==0)  n/=i,c[m]++;
		}
	}
	if(n>1)  p[++m]=n,c[m]=1;
	return m;
}

int main(){
	int q;  cin>>q;
	while(q--){
		ll n;  int k;  cin>>n>>k;
		int cnt=factor(n);  int m=1;
		for(int i=1;i<=cnt;i++){
			if(c[i]<k){
				for(int j=0;j<c[i];j++)  m*=p[i];
			}
	    }
	    cout<<n/m<<endl;
	}
	return 0;
}
















