#include<bits/stdc++.h>
using namespace std;

#define ll long long  //注意#define后面不用加分号
#define lc u<<1       //左儿子lc=2*u
#define rc u<<1|1     //右儿子rc=2*u+1
const ll N=1e5+5;
ll n,q,mod,w[N],op,x,y,k;
struct tree{
    ll l,r,sum,mul,add;   //mul,add为懒标记(可理解为记账)
}tr[4*N];                 //所有节点数最大不超过4*N

void pushup(ll u){  //向上更新
    tr[u].sum=(tr[lc].sum+tr[rc].sum)%mod;  //题目要求结果模mod
}

void calc(tree &t,ll m,ll a){  //计算函数,先乘后加(&引用操作直接修改)
    t.sum=(t.sum*m+(t.r-t.l+1)*a)%mod;
    //sum=(w[i]*m+a)(l<=i<=r)=sum*m+a*(l-r+1)
    t.mul=t.mul*m%mod;
    t.add=(t.add*m+a)%mod;  //更新mul,add
    //m0,a0为原标记,m,a为新加标记(也可能来自pushdown的父节点标记)
    //x*mul+add=(x*m0+a0)*m+a=x*m0*m+a0*m+a
    //mul=m0*m,add=a0*m+a
}

void pushdown(ll u){  //向下更新
    calc(tr[lc],tr[u].mul,tr[u].add);
    calc(tr[rc],tr[u].mul,tr[u].add);
    tr[u].add=0;  //清空懒标记
    tr[u].mul=1;
}

void build(ll u,ll l,ll r){  //建树
    tr[u]={l,r,w[l],1,0};  //mul,add初始为1,0
    if(l==r)  return;      //是叶子则返回
    ll mid=l+r>>1;         //不是叶子则裂开(+优先>>)
    build(lc,l,mid);
    build(rc,mid+1,r);
    pushup(u);             //更新父节点sum值
}

void change(ll u,ll x,ll y,ll m,ll a){  //区间修改(x到y区间所有数*m,+a)
    if(x<=tr[u].l&&y>=tr[u].r){    //覆盖则修改
        calc(tr[u],m,a);
        return;
    }
    ll mid=tr[u].l+tr[u].r>>1;     //不覆盖则裂开
    pushdown(u);                   //更新完子节点(处理完账)后再递归子节点
    if(x<=mid)  change(lc,x,y,m,a);
    if(y>mid)   change(rc,x,y,m,a);
    pushup(u);
}

ll query(ll u,ll x,ll y){  //区间查询
    if(x<=tr[u].l&&y>=tr[u].r)  return tr[u].sum;  //覆盖则返回
    ll mid=tr[u].l+tr[u].r>>1;                     //不覆盖则裂开
    pushdown(u);                                   //裂开后向下更新,保证子节点无账
    ll sum=0;
    if(x<=mid)  sum+=query(lc,x,y)%mod;
    if(y>mid)   sum+=query(rc,x,y)%mod;
    return sum%mod;
}

int main(){
    cin>>n>>q>>mod;
    for(int i=1;i<=n;i++)  cin>>w[i];
    build(1,1,n);
    while(q--){
        cin>>op>>x>>y;
        if(op==1){
            cin>>k;  change(1,x,y,k,0);  //区间*k(+0)
        }else if(op==2){
            cin>>k;  change(1,x,y,1,k);  //区间(*1)+k
        }else  cout<<query(1,x,y)<<endl;
    }
    return 0;
}