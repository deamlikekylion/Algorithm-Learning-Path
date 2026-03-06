#include<bits/stdc++.h>
using namespace std;
typedef long long ll;  
//typedef要加;(注意与#define的区别,ll与long long的位置也相反)

int n;
ll t[105],a[105],b[105];  //a,b数组分别存储相邻数字化简后的分子和分母

ll gcd(ll a,ll b){  //辗转相除求最大公约数
    if(b==0)  return a;
    else  return gcd(b,a%b);
    //t数组已经排序过,所以a(t[i+1])一定大于b(t[i]),不需要比较a,b的大小
}

//求出相邻比值的最大底数,最终使得a[i]=a[i+1]=它两的最大底数
//原理:最大底数为e,a[i]=e^x,a[i+1]=e^y,一直让它两中大的除以小的,最终a[i]=a[i+1]=e
void getbase(int i){
    if(a[i]==a[i+1])  return;  //相等时停止递归
    if(a[i]>a[i+1]){
        while(a[i]>a[i+1])  a[i]/=a[i+1];
        while(b[i]>b[i+1])  b[i]/=b[i+1];
        getbase(i);  //可能此时a[i+1]>a[i],所以继续递归
        return;
    }else{
        while(a[i+1]>a[i])  a[i+1]/=a[i];
        while(b[i+1]>b[i])  b[i+1]/=b[i];
        getbase(i);
        return;
    }
}

int main(){
    cin>>n;  for(int i=1;i<=n;i++)  cin>>t[i];
    sort(t+1,t+n+1);       //升序排序
    for(int i=1;i<n;i++){  //遍历去重
        if(t[i]==t[i+1]){  //记录重复元素个数k,将后面所有元素前移k
            int k=2;
            while(t[i]==t[i+k]&&i+k<=n)  k++;  //注意i+k<=n,防止k溢出
            k--;  n-=k;
            for(int j=i+1;j<=n;j++)  t[j]=t[j+k];
        }
    }
    for(int i=1;i<n;i++){
        ll g=gcd(t[i+1],t[i]);
        a[i]=t[i+1]/g;
        b[i]=t[i]/g;
    }
    a[0]=1;  b[0]=1;  //去重后如果n=1则输出等比值为1/1
    for(int i=1;i<n-1;i++)  getbase(i);  
    //所有相邻比值(一共n-1个)都是等比值的幂次,即等比值是其底数
    //所以所有相邻比值的最大底数即为最大等比值
    cout<<a[n-1]<<'/'<<b[n-1]<<endl;  //输出最后一个比值
    return 0;
}