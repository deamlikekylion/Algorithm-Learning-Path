#include<bits/stdc++.h>
using namespace std;

const int N=1e5+5;
int n,x,h[N],sum[N];

bool check(int y){
    for(int i=0;i<=n-y-1;i++){
        if(sum[i+y]-sum[i]<2*x)  return false;
    }
    return true;
}

int main(){
    cin>>n>>x;
    for(int i=1;i<=n-1;i++){
        cin>>h[i];
        sum[i]=h[i]+sum[i-1];
    }
    int l=1,r=n,ans;
    while(l<=r){
        int mid=(l+r)/2;
        if(check(mid)){
            r=mid-1;  ans=mid;
        }else  l=mid+1;
    }
    cout<<ans;
    return 0;
}