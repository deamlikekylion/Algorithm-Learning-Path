#include<bits/stdc++.h>
using namespace std;

#define ll long long    //注意#define后面不用加分号
#define lc u<<1         //左儿子lc=2*u
#define rc u<<1|1       //右儿子rc=2*u+1
const ll N=1e4+5;
ll x,y,k,w[N];
struct node{
    ll l,r,max,la;      //懒标记(维护最大值,直接记录该节点最大值即可)
}tr[4*N];               //所有节点数最大不超过4*N

void build(ll u,ll l,ll r){  //建树
    tr[u].l=l;  tr[u].r=r;  tr[u].la=0;
    if(l==r){
        tr[u].max=0;         //叶子初始max=0并返回
        return;
    }              
    ll m=l+r>>1;             //不是叶子则裂开(+优先>>)
    build(lc,l,m);
    build(rc,m+1,r);         //该题此处不用更新父节点max值
}

void pushdown(ll u){  //向下更新
    if(tr[u].la){
        tr[lc].max=max(tr[lc].max,tr[u].la);
        tr[rc].max=max(tr[rc].max,tr[u].la);
        tr[lc].la=max(tr[lc].la,tr[u].la);  //更新懒标记
        tr[rc].la=max(tr[rc].la,tr[u].la);
        tr[u].la=0;
    }
}

void change(ll u,ll x,ll y,ll k){
    if(x<=tr[u].l&&y>=tr[u].r){    //覆盖则修改
        tr[u].max=max(tr[u].max,k);
        tr[u].la=max(tr[u].la,k);  //更新懒标记
        return;
    }
    ll m=tr[u].l+tr[u].r>>1;       //不覆盖则裂开
    pushdown(u);                   //裂开后向下更新,保证子节点无账
    if(x<=m)  change(lc,x,y,k);
    if(y>m)   change(rc,x,y,k);
    tr[u].max=max(tr[lc].max,tr[rc].max);
}

ll query(ll u,ll x,ll y){  //区间查询
    if(x<=tr[u].l&&y>=tr[u].r)  return tr[u].max;  //覆盖则返回
    ll m=tr[u].l+tr[u].r>>1;                       //不覆盖则裂开
    pushdown(u);                                   //裂开后向下更新,保证子节点无账
    ll m1=0,m2=0;          
    if(x<=m)  m1=query(lc,x,y);
    if(y>m)   m2=query(rc,x,y);
    return max(m1,m2);
}

int main(){
    build(1,1,N);
    while(cin>>x>>k>>y)    change(1,x,y-1,k);  //注意为y-1
    for(int i=1;i<=N;i++)  w[i]=query(1,i,i);
    for(int i=1;i<=N;i++){
		if(w[i]!=w[i-1]){
			cout<<i<<' '<<w[i]<<' ';  //按照要求输出
		}
    } 
    return 0;
}