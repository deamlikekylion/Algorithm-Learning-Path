#include<bits/stdc++.h>
using namespace std;

#define ll long long
const ll N=1e5+5;
ll n,s,sum,ans;

struct node{
    ll p,c;
}a[N];

bool cmp(node x,node y){
    return x.c<y.c;
}

int main(){
    cin>>n>>s;
    for(ll i=1;i<=n;i++){
        cin>>a[i].p>>a[i].c;
        sum+=a[i].p;
    }
    sort(a+1,a+1+n,cmp);
    ll i=1,cnt=0;
    while(sum>=s){
        ans+=s*(a[i].c-cnt);
        cnt=a[i].c;
        sum-=a[i++].p;
        while(a[i].c==cnt){
            sum-=a[i++].p;
        }
    }
    for(;i<=n;i++){
        ans+=a[i].p*(a[i].c-cnt);
    }
    cout<<ans;
    return 0;
}