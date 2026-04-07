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