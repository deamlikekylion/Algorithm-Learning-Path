#include<bits/stdc++.h>
using namespace std;

#define ll long long    //注意#define后面不用加分号
#define lc u<<1         //左儿子lc=2*u
#define rc u<<1|1       //右儿子rc=2*u+1
#define INF 0x3f3f3f3f  //用于初始化区间最小值
const ll N=1e5+5;
ll n,m,w[N],x,y,k;
struct node{
    ll l,r,min=INF;
}tr[4*N];               //所有节点数最大不超过4*N

void build(ll u,ll l,ll r){  //建树
    tr[u].l=l;  tr[u].r=r;
    if(l==r){
        tr[u].min=w[l];                    //叶子更新min并返回
        return;
    }              
    ll m=l+r>>1;                           //不是叶子则裂开(+优先>>)
    build(lc,l,m);
    build(rc,m+1,r);
    tr[u].min=min(tr[lc].min,tr[rc].min);  //更新父节点sum值
}

ll query(ll u,ll x,ll y){  //区间查询
    if(x<=tr[u].l&&y>=tr[u].r)  return tr[u].min;  //覆盖则返回
    ll m=tr[u].l+tr[u].r>>1;                       //不覆盖则裂开
    int m1=INF,m2=INF;          
    if(x<=m)  m1=query(lc,x,y);
    if(y>m)   m2=query(rc,x,y);
    return min(m1,m2);
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)  cin>>w[i];
    build(1,1,n);
    while(m--){
        cin>>x>>y;
        cout<<query(1,x,y)<<' ';
    }
    return 0;
}