#include<bits/stdc++.h>
using namespace std;

#define ll long long
const ll N=1e5+5;
ll n,m,q,f[N],d[N];
//f[x]表示x所在并查集的根节点,d[x]表示x到其根节点f[x]的距离(模板P2024_食物链)
//此题中d[x]表示sum[x]-sum[根节点](根节点=find(x),sum为A数组前缀和)

//带权并查集的查找函数(带路径压缩),返回x的根节点,同时更新d[x]
ll find(ll x){
    if(f[x]==x)  return x;
    ll t=find(f[x]);    //递归找到x的根节点
    d[x]=d[x]+d[f[x]];  //路径压缩:更新x到根节点的权值
    //原d[x]是x到父节点的距离,d[f[x]]是父节点到根节点的距离
    //相加后就是x直接到根节点的距离
    return f[x]=t;      //路径压缩:直接让x的父节点为根节点
}

int main(){
    cin>>n>>m>>q;
    for(ll i=0;i<=n;i++)  f[i]=i;
    for(ll i=1;i<=m;i++){
        ll l,r,s;  cin>>l>>r>>s;  l--;
        //关键转化:区间[l,r]和=sum[r]-sum[l-1]=s,所以l--,对应前缀和sum[l]
        ll t1=find(l),t2=find(r);
        if(t1!=t2){    //如果两个节点不在同一个集合,合并
            f[t2]=t1;  //合并:让t2的父节点指向t1
            d[t2]=d[l]-d[r]+s;
            //核心公式:推导合并后的权值
            //已知sum[r]-sum[l]=s
            //d[r]=sum[r]-sum[t2],d[l]=sum[l]-sum[t1]
            //所以sum[r]=d[r]+sum[t2],sum[l]=d[l]+sum[t1]
            //s=sum[r]-sum[l]=(d[r]+sum[t2])-(d[l]+sum[t1])
            //因为sum[t1]=0(根节点),整理得:d[t2]=sum[t2]-sum[t1]=d[l]-d[r]+s
        }
    }
    while(q--){
        ll l,r;  cin>>l>>r;  l--;  //同样转化为sum[r]-sum[l-1]
        ll t1=find(l),t2=find(r);
        if(t1!=t2)  cout<<"UNKNOWN"<<endl;  
        //根节点不同→无法推导,输出UNKNOWN
        else  cout<<d[r]-d[l]<<endl;
        //根节点相同→可以推导,区间和=d[r]-d[l]
        //因为d[r]=sum[r]-sum[t2],d[l]=sum[l]-sum[t1],t1==t2
        //相减后就是d[r]-d[l]=sum[r]-sum[l]
    }
    return 0;
}