#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N=1e5+5;
ll n,sum[N],minn[N],size[N],fa[N],mina=INT_MAX,ans=0;
//sum[i]为环中所以点的值,minn[i]为环中的最小值,size[i]为环中点的个数
//fa[i]为并查集中i的父节点,mina为所有点的最小值(环外最小值)初始极小值
//同一环的点通过并查集指向同一父节点,环即为需要交换位置的点集合

struct node{              //结构体:存储元素的原始id和数值val
    ll id,val;
}a[N];  

bool cmp(node i,node j){  //用于升序排序的自定义排序函数
    return i.val<j.val;
}

ll find(ll x){            //并查集查找函数,顺便进行路径压缩
    if(fa[x]==x)  return x;
    return fa[x]=find(fa[x]);
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){                        
        cin>>a[i].val;  minn[i]=sum[i]=a[i].val;  //初始化环的最小值和权值和为自身数值
        fa[i]=a[i].id=i;  size[i]=1;              //初始化并查集,每个节点的父节点是自身,id为自身索引
        mina=min(mina,a[i].val);                  //更新最小值
    }
    sort(a+1,a+n+1,cmp);                   //按val升序排序
    for(int i=1;i<=n;i++){                 //遍历排序后的元素,并查集合并环
        if(a[i].id!=i){                    //若元素排序后位置不是自身,说明构成环(需交换位置)
            ll x=find(a[i].id),y=find(i);  //找到原始id和当前遍历位置的根
            if(x!=y){                      //若两个根不同,合并x到y,并更新y环的各项数值
                fa[x]=y;  minn[y]=min(minn[y],minn[x]);  
                sum[y]+=sum[x];  size[y]+=size[x];  
            }
        }
    }
    for(int i=1;i<=n;i++){  //遍历所有环的根节点,计算并累加每个环的最小代价
        if(fa[i]==i){  //环根节点的条件
            ans+=min(
                //策略1:使用环内最小值交换(用minn完成其他所有点的交换即为最小代价)
                (size[i]-1)*minn[i]+sum[i]-minn[i], 
                //策略2:使用环外最小值交换(先交换mina和minn,最后再换回来)
                (size[i]-1)*mina+sum[i]-minn[i]+2*(mina+minn[i]) 
            );
        }
    }
    cout<<ans;
    return 0;
}