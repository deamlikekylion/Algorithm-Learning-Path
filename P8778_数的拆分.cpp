#include<bits/stdc++.h>
using namespace std;

#define ll long long  //int上限2^31-1=2e9,long long上限2^63-1=9e18
const int N=4000;
vector<ll> p;
bool not_p[N+5];  //注意后面遍历时i<=N,此处数组要加5
//对于满足题目的a一定能表示成a=x1^2*x2^3,假设x1<x2,则x1^5<a<n=1e18
//所以x1<1e18的五次方根<4000,x1​一定是4000以内的数
//遍历4000内的所有质数(这些质数全是x1​的质因子),可以把x1​从a里彻底除干净​
//剩下的数字,就只能是x2的平方或者立方​

void init(){  //埃氏筛预处理质数,预处理得到4000以内的全部质数
    not_p[0]=not_p[1]=true;
    for(ll i=2;i<=N;i++){
        if(!not_p[i]){
            p.push_back(i);
            for(ll j=i+i;j<=N;j+=i)  not_p[j]=true;  //提前标记非质数
        }
    }
}

bool check(ll x){
    if(x==1)  return true;
    for(ll t : p){
        ll t2=t*t;
        if(x%t==0){
            if(x%t2!=0)  return false;
            while(x%t==0)  x/=t;
        }
        if(x==1)  return true;
    }
    ll y=sqrtl(x);  if(y*y==x)  return true;
    ll z=cbrtl(x);  if(z*z*z==x)  return true;
    //注意sqrtl和cbrtl函数,返回long double(去掉l的返回double,9e15)
    return false;
}

int main(){
    init();  ll t;  cin>>t;
    while(t--){
        ll x;  cin>>x;
        if(check(x))  cout<<"yes"<<endl;
        else  cout<<"no"<<endl;  
    }
    return 0;
}