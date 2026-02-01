#include<bits/stdc++.h>
using namespace std;

int n,k,ans;
const int N=1e5+5;
long long h[N],m[N],sum=0;

bool check(int x){
    int cnt=0;
    for(int j=1;j<=n;j++){
        cnt+=((h[j]/x)*(m[j]/x));
        if(cnt>=k)  break;
    }
    if(cnt>=k)  return true;
    else  return false;
}

int main(){
    cin>>n>>k;  
    for(int i=1;i<=n;i++)  cin>>h[i]>>m[i];
    int l=1,r=100000;
    while(l<=r){                
        int mid=(l+r)/2;
        if(check(mid)){
            l=mid+1;  ans=mid;  
        }else r=mid-1;           
    }
    cout<<ans;
    /*二分模板:
    while(l<=r){
        int mid=(l+r)/2;
        if(check(mid)){
            l=mid+1;  ans=mid;
        }else  r=mid-1;
    }
    cout<<ans;
    其中l=mid+1和r=mid-1视check的具体情况可换位置
    */
    return 0;
}