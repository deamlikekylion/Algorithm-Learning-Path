#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll fastPow(ll a,ll n,ll m){
	if(n==0)  return 1;
	if(n==1)  return a%m;
	ll t=fastPow(a,n/2,m);
	if(n%2==1)  return (t%m*t%m)*a%m;
	else  return t%m*t%m;
}

int main(){
	ll a,n,m;  cin>>a>>n>>m;
	cout<<fastPow(a,n,m);
	return 0;
}
