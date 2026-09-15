#include<bits/stdc++.h>
using namespace std;

const int N=1e6+5;
int n,a,fa[N];    //fa[i]为并查集父数组

int find(int x){  //并查集查询操作
    if(x==fa[x])  return x;
    return fa[x]=find(fa[x]);
}

int main(){                          //此题用哈希会TLE一个点,并查集更快
    cin>>n;
    for(int i=1;i<=N;i++)  fa[i]=i;  //初始每个数字父节点为自己
    for(int i=1;i<=n;i++){
        cin>>a;
        a=find(a);  //查询a的父节点并将父节点的值赋值给a,第一次查询a就是自己
        fa[a]=a+1;  //将a的父节点加1,后面出现重复a时就会被赋值为a+1
        cout<<a<<' ';
    }
    return 0;
}