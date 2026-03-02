#include<bits/stdc++.h>
using namespace std;

#define ll long long     //注意后面不要加冒号
const ll N=1e5+5;
ll n,k,a,s[N],b[N],ans;  //s[i]为数组前缀和,b[i]为s数组中模k结果为i的个数

int main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>a;  s[i]=s[i-1]+a;  //初始前缀和
    }
    for(int i=0;i<=n;i++){
        ans+=b[s[i]%k]++;
        //如果l到r区间为k的倍数则s[r]-s[l-1]为k的倍数即s[r]与s[l-1]同余k
        //所以记录每次s[i]%k的个数,重复时说明同余k,ans+1(b首次记录时ans+=0不变)
        //注意此处s[i]为l-1到r范围,1<=l,r<=n,所以0<=i<=n
    }
    cout<<ans;
    return 0;
}