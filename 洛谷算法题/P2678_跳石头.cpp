#include<bits/stdc++.h>
using namespace std;

int d,n,m,a[50005];

bool judge(int x){
    int cnt=0,i=0,now=0;
    while(i<n+1){
        i++;
        if(a[i]-a[now]<x)  cnt++;
        else now=i;
    }
    if(cnt>m)  return false;
    else  return true;
}

int main(){
    cin>>d>>n>>m;  a[0]=0;  a[n+1]=d;
    for(int i=1;i<=n;i++)  cin>>a[i];
    int l=1,r=d,mid,ans;
    while(l<=r){
        mid=(l+r)/2;
        if(judge(mid)){
            ans=mid;  l=mid+1;
        }else  r=mid-1;
    }
    cout<<ans;
    return 0;
}