#include<bits/stdc++.h>
using namespace std;

#define ll long long
const int N=1e5+5;
ll n,a[N],p[N],w[25][2],ans;
//p为前缀异或和数组,p[i]为前i个数的异或和
//w[k][0]=所有p数组中第k位为0的数量,w[k][1]=第k位为1的数量

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];  p[i]=p[i-1]^a[i];  //计算前缀异或和数组
    }
    /*所有子数组的异或和总和=所有i>j的p[i]^p[j]之和
      只有0^1或1^0的组合,才会让第k位为1,进而产生贡献。
      在p[0]~p[n]中,满足第k位一个是0,一个是1的有序数对(i,j)且i>j有多少个？
      这里用乘法原理最直观:
      第一步:从所有第k位为0的数中选1个,有cnt0种选法
      第二步:从所有第k位为1的数中选1个,有cnt1种选法
      根据乘法原理,完成这两步的总组合数=第一步选法×第二步选法=cnt0×cnt1.*/
    for(int i=0;i<=n;i++){        //遍历所有前缀异或值:p[0]~p[n]
        for(int k=0;k<=20;k++){   //遍历0~20位(题目说a[i]≤2^20,只需算这21位)
            int bit=(p[i]>>k)&1;  //取出p[i]的第k位二进制数字
            w[k][bit]++;
        }
    }
    for(int k=0;k<=20;k++)  ans+=w[k][0]*w[k][1]*(1<<k);
    //计算每一位的贡献,累加得到答案
    //第k位贡献=0的个数×1的个数×2^k
    cout<<ans;
    return 0;
}