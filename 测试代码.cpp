#include<bits/stdc++.h>
#define int long long //一定要开long long
using namespace std;
int n,k,s[100005],ans=0,b[100005];//s前缀和数组，b用于存储前缀和的模数
signed main(){
    cin>>n>>k;
    for(int i=1,t;i<=n;i++)
        cin>>t,s[i]=s[i-1]+t; //输入并计算前缀和
    for(int i=0;i<=n;i++)//注意！必须从0开始，因为0的位置也能和后面的下标构成满足条件的子序列
        ans+=b[s[i]%k]++;//统计答案的同时也要加上当前余数，方便为以后的i服务
    cout<<ans;
    return 0;
}
