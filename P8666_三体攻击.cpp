#include<bits/stdc++.h>
using namespace std;
#define ll long long  //注意测试数据较大

const ll N=1e6+5;
ll A,B,C,n,m;
ll s[N],D[N],sx[N],tx[N],sy[N],ty[N],sz[N],tz[N],h[N];
//s数组存储飞船生命值,h数组为每轮攻击的值,D数组为每个飞船收到的总攻击的差分值
//对D求前缀和为对应飞船受到的总攻击值(差分为前缀和逆运算,对差分数组求前缀和得原数组)
//sx,tx,sy,ty,sz,tz为每轮攻击的范围(注意不能用x1,x2,y1,y2,z1,z2,因为y1是一个函数)

ll tran(ll x,ll y,ll z){  //压维:将三维转换为一维
    if(x>A||y>B||z>C)  return 0;
    return ((x-1)*B+(y-1))*C+(z-1)+1;
}

bool check(ll x){  //二分检查函数
    for(ll i=1;i<=n;i++)  D[i]=0;  //初始总攻击值差分数组为0
    for(ll i=1;i<=x;i++){          //用三维差分数组记录区间修改值(每轮攻击值)
        D[tran(sx[i]  ,sy[i]  ,sz[i]  )]+=h[i];
        D[tran(tx[i]+1,sy[i]  ,sz[i]  )]-=h[i];
        D[tran(sx[i]  ,sy[i]  ,tz[i]+1)]-=h[i];
        D[tran(tx[i]+1,sy[i]  ,tz[i]+1)]+=h[i];
        D[tran(sx[i]  ,ty[i]+1,sz[i]  )]-=h[i];
        D[tran(tx[i]+1,ty[i]+1,sz[i]  )]+=h[i];
        D[tran(sx[i]  ,ty[i]+1,tz[i]+1)]+=h[i];
        D[tran(tx[i]+1,ty[i]+1,tz[i]+1)]-=h[i];
    }
    //求x,y,z三个方向的前缀和
    for(ll i=1;i<=A;i++){         //把x,y看作定值累加求z方向前缀和
        for(ll j=1;j<=B;j++){
            for(ll k=1;k<C;k++){  
                D[tran(i,j,k+1)]+=D[tran(i,j,k)];
            }
        }
    }            
    for(ll i=1;i<=A;i++){         //把x,z看作定值累加求y方向前缀和
        for(ll k=1;k<=C;k++){
            for(ll j=1;j<B;j++){  
                D[tran(i,j+1,k)]+=D[tran(i,j,k)];
            }
        }
    }            
    for(ll j=1;j<=B;j++){         //把y,z看作定值累加求x方向前缀和
        for(ll k=1;k<=C;k++){
            for(ll i=1;i<A;i++){  
                D[tran(i+1,j,k)]+=D[tran(i,j,k)];
            }
        }
    }
    for(ll i=1;i<=n;i++){         //如果有一个飞船被摧毁则返回true减少轮数
        if(D[i]>s[i])  return true;
    }
    return false;                 //无飞船被摧毁返回false增大轮数
}

int main(){
    cin>>A>>B>>C>>m;  n=A*B*C;
    for(ll i=1;i<=n;i++)  cin>>s[i];
    for(ll i=1;i<=m;i++)  cin>>sx[i]>>tx[i]>>sy[i]>>ty[i]>>sz[i]>>tz[i]>>h[i];
    ll l=1,r=m,ans;
    while(l<=r){  //二分查找第几轮时开始出现飞船被摧毁
        ll mid=(l+r)/2;
        if(check(mid)){
            r=mid-1;  ans=mid;
        }else  l=mid+1;
    }
    cout<<ans;
    return 0;
}