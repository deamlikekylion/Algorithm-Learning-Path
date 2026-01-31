#include<bits/stdc++.h>
using namespace std;

#define ll long long  //注意#define后面不用加分号
#define lc u<<1       //左儿子lc=2*u
#define rc u<<1|1     //右儿子rc=2*u+1
const ll N=1e5+5;
ll n,m,w[N],op,x,y,k;
struct node{
    ll l,r,sum,add;   //add为懒标记,可理解为记账
}tr[4*N];             //所有节点数最大不超过4*N

void pushup(ll u){  //向上更新
    tr[u].sum=tr[lc].sum+tr[rc].sum;
}

void pushdown(ll u){  //向下更新
    if(tr[u].add){
        tr[lc].sum+=tr[u].add*(tr[lc].r-tr[lc].l+1);
        tr[rc].sum+=tr[u].add*(tr[rc].r-tr[rc].l+1);
        tr[lc].add+=tr[u].add;
        tr[rc].add+=tr[u].add;
        tr[u].add=0;
    }
}

void build(ll u,ll l,ll r){  //建树
    tr[u]={l,r,w[l],0};
    if(l==r)  return;  //是叶子则返回
    ll m=l+r>>1;       //不是叶子则裂开(+优先>>)
    build(lc,l,m);
    build(rc,m+1,r);
    pushup(u);         //更新父节点sum值
}

void change(ll u,ll x,ll y,ll k){  //区间修改
    if(x<=tr[u].l&&y>=tr[u].r){    //覆盖则修改
        tr[u].sum+=k*(tr[u].r-tr[u].l+1);
        tr[u].add+=k;
        return;
    }
    ll m=tr[u].l+tr[u].r>>1;       //不覆盖则裂开
    pushdown(u);                   //裂开后向下更新,保证子节点无账
    if(x<=m)  change(lc,x,y,k);
    if(y>m)   change(rc,x,y,k);
    pushup(u);
}

ll query(ll u,ll x,ll y){  //区间查询
    if(x<=tr[u].l&&y>=tr[u].r)  return tr[u].sum;  //覆盖则返回
    ll m=tr[u].l+tr[u].r>>1;                       //不覆盖则裂开
    pushdown(u);                                   //裂开后向下更新,保证子节点无账
    ll sum=0;
    if(x<=m)  sum+=query(lc,x,y);
    if(y>m)   sum+=query(rc,x,y);
    return sum;
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)  cin>>w[i];
    build(1,1,n);
    while(m--){
        cin>>op>>x>>y;
        if(op==1){
            cin>>k;  change(1,x,y,k);
        }else  cout<<query(1,x,y)<<endl;
    }
    return 0;
}