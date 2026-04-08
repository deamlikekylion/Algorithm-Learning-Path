#include<bits/stdc++.h>
using namespace std;

#define ll long long
const ll mod=1000000007,N=5e5+5;
ll sum,nm,x,ans,a[N],jc[N],invjc[N];
//a[i]表示数字i出现的次数,jc[i]表示i!(i的阶乘)取模,invjc[i]表示i!模1e9+7的逆元

ll qpow(ll a,ll b){  //快速幂函数,计算a^b取模,用于求逆元
    ll res=1;
    while(b){
        if(b&1)  res=(res*a)%mod;
        a=(a*a)%mod;
        b>>=1;
    }
    return res;
}

ll inv(ll x){  //求x在模mod下的逆元(费马小定理:mod如果是质数,则逆元=x^(mod-2)取模)
    return  qpow(x,mod-2);
}

//int上限2^31-1=2e9,long long上限2^63-1=9e18


const int N=4000;
vector<ll> p;
bool not_p[N+5];      //注意后面遍历时i<=N,此处数组要加5
void init(){  //埃氏筛预处理质数,预处理得到4000以内的全部质数
    not_p[0]=not_p[1]=true;
    for(ll i=2;i<=N;i++){
        if(!not_p[i]){
            p.push_back(i);
            for(ll j=i+i;j<=N;j+=i)  not_p[j]=true;  //提前标记非质数
        }
    }
}