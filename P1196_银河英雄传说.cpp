#include<bits/stdc++.h>
using namespace std;

const int N=3e4;
int f[N],d[N],siz[N];
//f[x]表示x所在队列的根节点,d[x]表示x到其根节点f[x]的距离,siz[x]表示以x为根的队列的大小


int find(int x){
    if(f[x]==x)  return x;
    int t=find(f[x]);  //记录新根t
    d[x]+=d[f[x]];     //先更新x到新根t的距离(x到原根节点的距离+原根节点到新根的距离)
    return f[x]=t;     //在更新f[x]同时路径压缩
}

int main(){
    for(int i=1;i<=N;i++)  f[i]=i,siz[i]=1;  //初始化并查集
    int t;  cin>>t;
    while(t--){ 
        char op;  int x,y;  cin>>op>>x>>y;
        if(op=='M'){  //合并,x队列接到y队列后面
            int tx=find(x),ty=find(y);  //找到x,y的根节点tx,ty
            f[tx]=ty;  d[tx]=siz[ty];  siz[ty]+=siz[tx];
            //x队列接到y队列后面,更新tx到ty的距离(tx子节点在find中更新距离),在根上更新队列大小
        }else{
            if(find(x)!=find(y))  cout<<"-1"<<endl;  //x,y不在同一队列
            else  cout<<abs(d[x]-d[y])-1<<endl;      //find后d已更新,输出xy之间的元素个数
        }
    }
    return 0;
}