#include<bits/stdc++.h>
using namespace std;

#define ll long long
const ll N=2e5+5;
ll n,sum,ans,a[N],b[N];

int main(){
    cin>>n;
    for(ll i=1;i<=n;i++)  cin>>a[i],sum+=a[i];
    b[1]=sum-a[1];
    for(ll i=2;i<=n;i++)  b[i]=b[i-1]-a[i];
    for(ll i=1;i<=n;i++)  ans+=a[i]*b[i];
    cout<<ans;
    return 0;
}