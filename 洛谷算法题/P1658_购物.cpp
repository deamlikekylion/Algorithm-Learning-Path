#include<bits/stdc++.h>
using namespace std;

int main(){
    int x,n,a[15],sum=0,ans=0;  cin>>x>>n;
    for(int i=1;i<=n;i++)  cin>>a[i];
    sort(a+1,a+n+1);  
    if(a[1]!=1){                //最小的不是1,则不能组合值1
        cout<<"-1";  return 0;
    }
    while(sum<x){               //sum为当前可以组合出1到sum之间的任意值
        for(int i=n;i>=1;i--){  //优先选面值大的
            if(a[i]<=sum+1){    //不能超过sum+1,否则组合的新值最小为sum+2,不能组合出sum+1
                sum+=a[i];      //更新sum
                ans++;          //硬币数加1
                break;
            }
        }
    }
    cout<<ans;
    return 0;
}