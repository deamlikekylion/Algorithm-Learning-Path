#include<bits/stdc++.h>
using namespace std;

const int N=5e4+5;
int n,m,op,x,y,ans;
int f[N],d[N];         
//f[x]表示x所在并查集的根节点,d[x]表示x到其根节点f[x]的距离
//该题中在同一并查集中的动物已经建立了关系,具体由(d[x]-d[y])%3的值决定
//为0表示同类,为1表示y是x的猎物,为2表示y是x的天敌
//可见动物被划分到并查集树的不同图层

int find(int x){
    if(f[x]==x)  return x;
    int t=find(f[x]);  //记录新根t
    d[x]+=d[f[x]];     //先更新x到新根t的距离(x到原根节点的距离+原根节点到新根的距离)
    return f[x]=t;     //在更新f[x]同时路径压缩
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)  f[i]=i;
    while(m--){
        cin>>op>>x>>y;
        if(x>n||y>n)  ans++;
        else{
            int tx=find(x),ty=find(y);  //找到x,y的根节点tx,ty
            if(op==1){                  //x,y是同类情况
                if(tx==ty&&((d[x]-d[y])%3+3)%3!=0)  ans++;
                //x,y在同一颗树且不在同一层,则不是同类,是假话
                //注意cpp中%3可能为负数所以(d[x]-d[y])%3后加3在%3保证结果为0或1或2
                if(tx!=ty){             //x,y不在同一颗树,则合并集合
                    f[tx]=ty;           //tx指向ty
                    d[tx]=d[y]-d[x];    //x,y应在同一层,到根的距离应相等((d[x]-d[y])%3=0)
                                        //d[tx]=d[y]-d[x],则find(x)更新d[x]时
                                        //d[x]+=d[tx]=d[y],x到根的距离等于y
                }
            }else{                      //x吃y情况
                if(tx==ty&&((d[x]-d[y])%3+3)%3!=1)  ans++;
                //x,y在同一颗树且x不在y的下一层,则不满足x吃y,是假话
                if(tx!=ty){             //x,y不在同一颗树,则合并集合
                    f[tx]=ty;           //tx指向ty
                    d[tx]=d[y]-d[x]+1;  //x应在y的下一层,到根的距离应多1((d[x]-d[y])%3=1)
                                        //d[tx]=d[y]-d[x]+1,则find(x)更新d[x]时
                                        //d[x]+=d[tx]=d[y]+1,x到根的距离比y多1
                }
            }
        }
    }
    cout<<ans;
    return 0;
}