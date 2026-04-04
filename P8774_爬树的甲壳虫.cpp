#include<bits/stdc++.h>
using namespace std;

const int N=1e5+5,P=998244353;
int n,x[N],y[N];

int fp(int a,int k){  //快速幂函数:求(a^k)%P
    int res=1;
    for(;k;k>>=1){  
    //遍历指数k的每一个二进制位,直到k=0结束
    //>>为右移,>>=1右移一位相当于/2,舍弃检查过的二进制位(最低位)
        if(k&1)  res=(1ll*a*res)%P;
        //检查当前二进制位(最低位)是否为1,为1就把当前的a乘进结果
        a=(1ll*a*a)%P;
        //核心操作:底数每次平方,对应二进制位的权重翻倍
    }
    return res;
}

int main(){
    cin>>n;  
    for(int i=1;i<=n;i++)  cin>>x[i]>>y[i];
    int s1=1,s2=0,s3=0;
    //E(i) = 1 + P(i+1) * E(0) + (1 - P(i+1)) * E(i+1)
    //递推可得E(0)=s1*E(n)+s2*E(0)+s3,E(n)=0
    //所以E(0)=s3/(1-s2)
    //s1:对应公式中的累乘项 ∏(1-p_j)  j从1到i-1，初始为1（空乘积）
    //s2:对应公式中的系数项 ∑[ p_i * ∏(1-p_j) ]
    //s3:对应公式中的常数项 ∑[ ∏(1-p_j) ]
    for(int i=1;i<=n;i++){
        int p1=(1ll*x[i]*fp(y[i],P-2))%P;
        int p2=(1ll*(y[i]-x[i])*fp(y[i],P-2))%P;
        //p1 = p_i = x_i / y_i
        //p2 = 1-p_i = (y_i - x_i)/y_i
        //1ll是防止两数相乘int溢出转换成long long,后面%P有变回int
        //费马小定理:y^(P-1)与1模P同余,所以y^(P-2)同余于1/y
        //x/y=x*(1/y)=x*(y^(P-2))=x*fp(y,P-2)
        s3=(s3+s1)%P;
        s2=(s2+1ll*s1*p1)%P;
        s1=(1ll*s1*p2)%P;
        //s3 += 累乘项 ∏(1-p_j)  j从1到i
        //s2 += p_i * 累乘项 ∏(1-p_j)  j从1到i-1
        //s1 = 累乘项 ∏(1-p_j)  j从1到i （为下一轮循环准备）
    }
    int ans=(1ll*s3*fp(1-s2+P,P-2))%P;
    //ans=E(0)=s3/(1-s2)=s3*fp(1-s2,P-2)=s3*fp(1-s2+P,P-2)
    //1-s2可能为负数,加P保证为正数
    cout<<ans;
    return 0;
}