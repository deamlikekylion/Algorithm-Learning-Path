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

int main(){
    cin>>sum;  nm=sum-2;  jc[1]=1;
    for(ll i=2;i<=5e5;i++)  jc[i]=(jc[i-1]*i)%mod;  //预处理阶乘数组
    for(ll i=0;i<=5e5;i++)  invjc[i]=inv(jc[i]);    //预处理阶乘的逆元数组
    for(ll i=1;i<=sum;i++)  cin>>x,a[x]++;          //读取数字,统计每个数字的出现次数
    for(ll i=1;i<=nm;i++){      //枚举所有可能的矩阵行数n,寻找合法的(n,m)组合
        if(nm%i==0&&a[i]&&a[nm/i]){
            ll n=i,m=nm/i;  
            a[n]--;  a[m]--;    //临时扣除n和m的计数
            ll now=jc[nm];
            for(int j=1;j<=5e5;j++){
                if(a[j])  now=(now*invjc[a[j]])%mod;  //数字j重复
            }
            //计算当前(n,m)对应的合法矩阵数:now = (n * m)! / (a1! * a2! * ... * at!)
			//其中ai是重复数字i的出现次数,模意义下除法=乘逆元
            ans=(ans+now)%mod;  //累加当前情况的结果到总答案
            a[n]++;  a[m]++;    //恢复n和m的计数
        }
    }
    cout<<ans<<endl;
    return 0;
}