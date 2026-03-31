#include<bits/stdc++.h>
using namespace std;

#define ll long long
const ll N=1e5+5;
ll n,k,t,a[N],b[N],sum[N],sum2[N];

bool check(ll x){
    for(ll i=1;i<=x;i++)  b[i]=a[i];
    sort(b+1,b+1+x);
    for(ll i=1;i<=x;i++){
        sum[i]=sum[i-1]+b[i];
        sum2[i]=sum2[i-1]+b[i]*b[i];
    }
    double res=(double)t+1.0;
    for(ll i=k;i<=x;i++){
        double s1=(double)sum2[i]-(double)sum2[i-k];
        double s2=2.0*((double)sum[i]-(double)sum[i-k])*(((double)sum[i]-(double)sum[i-k])/(double)k);
        double s3=(((double)sum[i]-(double)sum[i-k])/(double)k)*(((double)sum[i]-(double)sum[i-k])/(double)k)*k;
        res=min(res,(s1-s2+s3)/(double)k);
    }
    return res<t;
}

int main(){
    cin>>n>>k>>t;  for(ll i=1;i<=n;i++)  cin>>a[i];
    ll l=k,r=n,ans=-1;
    while(l<=r){
        ll mid=(l+r)>>1;
        if(check(mid)){
            ans=mid;  r=mid-1;
        }else  l=mid+1;
    }
    cout<<ans;
    return 0;
}