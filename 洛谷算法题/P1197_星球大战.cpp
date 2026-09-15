#include<bits/stdc++.h>
using namespace std;

const int N=4e5+5;
int h[N],from[N],to[N],ne[N],idx;  //链式前向星相关变量
int n,m,k,x,y,tot;  //tot连通块数
int a[N],be[N],f[N],ans[N];
 //a[i]为第i个被摧毁的星球,be标记星球是否被摧毁
 //f[x]表示x所在并查集的根节点,ans[i]为第i次攻击后的连通块数

void add(int u,int v){  //链式前向星邻接表加边
    from[++idx]=u;  to[idx]=v;
    ne[idx]=h[u];  h[u]=idx;
}

int find(int x){  //带路径压缩的并查集查找函数
    if(f[x]==x)  return x;
    return f[x]=find(f[x]);
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)  f[i]=i;  //并查集初始化
    for(int i=1;i<=m;i++){
        cin>>x>>y;  add(x,y);  add(y,x);  //无向边,双向添加到邻接表
    }
    cin>>k;
    for(int i=1;i<=k;i++){
        cin>>x;  a[i]=x;  be[x]=1;  //记录被摧毁的星球x同时标记x被摧毁
    }
    tot=n-k;  //初始tot为剩余星球独立成块
    for(int i=1;i<=2*m;i++){  //枚举所有边
        int x=from[i],y=to[i],tx=find(x),ty=find(y);
        if(!be[x]&&!be[y]&&tx!=ty){  //两球都没被摧毁且没在同一集合,则合并
            f[tx]=ty;  
            tot--;  //合并后,连通块数-1
        }
    }
    ans[k+1]=tot;  //摧毁k个星球后的答案
    for(int j=k;j>=1;j--){  //把摧毁的星球逆向修复
        x=a[j];  be[x]=0;  tot++;  //因为修复一个点,连通块数+1
        for(int i=h[x];i;i=ne[i]){  //枚举x的邻接点
            int y=to[i],tx=find(x),ty=find(y);
            if(!be[y]&&tx!=ty){  //两球都没被摧毁且没在同一集合,则合并
                f[tx]=ty;  
                tot--;  //合并后,连通块数-1
            }
        }  
        ans[j]=tot;  //修复完这个点后,连通块的个数 
    }
    for(int i=1;i<=k+1;i++)  cout<<ans[i]<<endl;  //输出每次摧毁后的答案
    return 0;
}